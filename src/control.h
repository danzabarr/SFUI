#pragma once

#include <functional>
#include <string>
#include <concepts>
#include <iostream>
#include <type_traits>
#include <typeindex>

namespace sfui
{
	using func = std::ostream & (*)(std::ostream&, const std::any&);

	std::unordered_map<std::type_index, func> from_any
	{
		{std::type_index(typeid(int)),
			 [](auto& o, const std::any& a)-> std::ostream& { return o << std::any_cast<int>(a); }},
		{std::type_index(typeid(double)),
			 [](auto& o, const std::any& a)-> std::ostream& { return o << std::any_cast<double>(a); }},
		{std::type_index(typeid(std::string)),
			 [](auto& o, const std::any& a)-> std::ostream& { return o << std::any_cast<std::string>(a); }}
	};

	inline decltype(auto) operator<<(std::ostream& o, const std::any& a)
	{
		return sfui::from_any[std::type_index(a.type())](o, a);
	}

	template<typename TTuple, typename UTuple, std::size_t... Indices>
	static constexpr bool is_convertible_tuple(std::index_sequence<Indices...>) {
		return
			// Parameter counts match
			std::tuple_size<TTuple>::value == std::tuple_size<UTuple>::value &&

			// All types are convertible
			(
				... &&
				std::is_convertible
				<
				std::tuple_element_t<Indices, TTuple>,
				std::tuple_element_t<Indices, UTuple>
				>::value
				);
	}

	template<typename TTuple, typename UTuple>
	static constexpr bool is_convertible_tuple()
	{
		return std::is_convertible<TTuple, UTuple>(std::make_index_sequence<std::tuple_size_v<TTuple>> {});
	}

	//----------- Forward Declarations----------------
	template <typename... T>
	class Control;

	template <typename... T>
	class DataModel;

	
	//----------- Declaration of Control----------------

	/// <summary>
	/// A Control is an interface for dispatching callbacks to different kinds of listeners and bindings.
	/// It can be extended to define a specific kind of control.
	/// A Control<bool> would be extended to define a Toggle.
	/// </summary>
	/// <typeparam name="...T"></typeparam>
	template <typename... T>
	class Control //: public DataModel<T...>
	{
		friend class DataModel<T...>;

		template<typename... Params>
		static constexpr bool has_convertible_params = false;

		template<typename... Params>
		static constexpr bool has_convertible_params<Params...> =
			std::is_convertible<std::tuple<Params...>, std::tuple<T...>>();

	public:

		~Control();
		/// <summary>
		/// Bind a callback to this control. The callback will be called when the control is interacted with.
		/// </summary>
		/// <param name="callback"></param>
		//void bind(std::function<void(T...)> callback);

		//template <typename...Params>
		void bind(std::function<void(T...)> callback) //requires has_convertible_params<Params...>
		{
			bindings.push_back(callback);
		}

		/// <summary>
		/// Bind a data model to this control. The control will be updated when the data model is updated.
		/// The control will also update the data model when it is interacted with.
		/// You can also pass a control to this method, and it will bind as an alias.
		/// </summary>
		/// <param name="model"></param>
		void bind(DataModel<T...>& model);

		//void bind(Control<T...>& control) override;

		/// <summary>
		/// Bind an element action to this control. The action will be called on the element when the control is interacted with.
		/// </summary>
		/// <param name="e"></param>
		/// <param name="action"></param>
		void bind(Element& e, const std::string& action);

		/// <summary>
		/// Removes all bindings.
		/// This will kill the control from updating anything.
		/// However, references to this may still exist on other objects.
		/// </summary>
		void unbind();


		/// <summary>
		/// This method is intended to be overwritten by different implementations of controls.
		/// It should handle updating the current display with the new data.
		/// For example, a Toggle would receive a bool, and would update its display to reflect the new value.
		/// A Field would receive a FieldEvent which contains details on how to change the text currently being displayed.
		/// </summary>
		/// <param name="...value"></param>
		virtual void display(const T&... value);

		//void notify(T... value) override;

		/// <summary>
		/// Pushes data to all bound callbacks and models.
		/// </summary>
		/// <typeparam name="...Params"></typeparam>
		/// <param name="...parameters"></param>
		template<typename... Params> requires has_convertible_params<Params...>
		void push(Params&&... parameters) const
		{
			for (DataModel<T...>* model : models)
				model->notify(std::forward<Params>(parameters)...);

			for (const std::function<void(T...)>& binding : bindings)
				binding(std::forward<Params>(parameters)...);
		}

	private:
		std::vector<std::function<void(T...)>> bindings {};
		std::vector<DataModel<T...>*> models {};
		
	};

	//----------- Declaration of DataModel----------------

	/// <summary>
	/// A DataModel is an interface for transferring data between controls and underlying sources of data.
	/// For example a Field is a control for editing a document, 
	/// A FieldModel is a type of DataModel that holds the data that is transferred between the Field and the document.
	/// used to 
	/// </summary>
	/// <typeparam name="...T"></typeparam>
	template <typename... T>
	class DataModel
	{
		friend class Control<T...>;
	public:
		~DataModel();

		/// <summary>
		/// Bind a control to this data model. The control will be updated when the data model is updated.
		/// This is the same as calling control.bind(model).
		/// </summary>
		/// <param name="control"></param>
		virtual void bind(Control<T...>& control);

		/// <summary>
		/// Notifies all controls bound to this model to change their displayed value.
		/// If this is a control object, it notifies only its aliases, not its model.
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="value"></param>
		virtual void notify(T... values);

		/// <summary>
		/// Performs validation on the given value. If the value is invalid, it will be corrected.
		/// </summary>
		/// <param name="...value"></param>
		/// <returns></returns>
		virtual bool validate(T&... values);

		/// <summary>
		///	Resets the model.
		/// It will no longer update any controls.
		/// It may still be updated by controls that it is bound to.
		/// </summary>
		void reset();

	private:
		std::vector<Control<T...>*> controls;
	};

	//----------- Method definitions of Control----------------
	template <typename... T>
	Control<T...>::~Control()
	{
		std::cout << "Called the Control destructor" << std::endl;
		unbind();
	}

	//template <typename... T>
	//void Control<T...>::notify(T... values)
	//{
	//	DataModel<T...>::notify(values...);
	//	display(values...);
	//}

	template <typename... T>
	void Control<T...>::display(const T&... args)
	{
		std::cout << "Displaying " << (void*)this << ": ";
		((std::cout << args << ", "), ...);
		std::cout << "\b\b " << std::endl;
	}

	
	
	//template <typename... T>
	//void Control<T...>::bind(Control<T...>& control)
	//{
	//	if (std::find(this->controls.begin(), this->controls.end(), &control) == this->controls.end())
	//		this->controls.push_back(&control);
	//	else
	//		std::cout << "Control already bound to model" << std::endl;
	//	//control.bind([this](T... value) { this->notify(value...); });
	//}

	
	template <typename... T>
	void Control<T...>::bind(Element& e, const std::string& action)
	{
		bindings.push_back(e.get_function<T...>(action));
	}

	template <typename... T>
	void Control<T...>::bind(DataModel<T...>& model)
	{
		model.bind(*this);
	}

	template <typename... T>
	void Control<T...>::unbind()
	{
		for (DataModel<T...>* model : models)
			model->controls.erase(std::remove(model->controls.begin(), model->controls.end(), this), model->controls.end());
		models.clear();
		bindings.clear();
	}

	//----------- Method definitions of Control----------------
	template <typename... T>
	DataModel<T...>::~DataModel()
	{
		std::cout << "Called the DataModel destructor" << std::endl;
		reset();
	}

	template <typename... T>
	void DataModel<T...>::bind(Control<T...>& control)
	{
		if (std::find(controls.begin(), controls.end(), &control) == controls.end())
		{
			controls.push_back(&control);
			control.models.push_back(this);
			//control.bind([this](T... value) { this->notify(value...); });
			//control.controls.push_back(this);
		}
		else
			std::cout << "Control already bound to model" << std::endl;
	}
	
	template <typename... T>
	void DataModel<T...>::notify(T... values)
	{
		for (Control<T...>* control : controls)
			if (validate(values...))
				control->display(values...);
	}

	template <typename...T>
	bool DataModel<T...>::validate(T&... values)
	{
		return true;
	}

	template <typename... T>
	void DataModel<T...>::reset()
	{
		controls.clear();
	}
}
