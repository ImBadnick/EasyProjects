import React, {useState, useRef, useEffect} from 'react';
import TodoList from './TodoList.js';
import uuidv4 from 'uuid/v4';

const LOCAL_STORAGE_KEY = 'todoApp.todos' //Key of the local storage, used to save and get the localStorage value

function App() {
  const [todos, setTodos] = useState([]) //useState returns the current state and a method for update the state
  const TodoInputName=useRef() //Create a variable that takes the name of the reference in the input field and uses "useRef()" to take the value of the field.
  
  //Called when the DOM has changes
  useEffect(() => {
    const storedTodos = JSON.parse(localStorage.getItem(LOCAL_STORAGE_KEY)) //getItem returns the value of the parameter.
    //JSON.parse transform the JSON string in a javascript's value/object
    if (storedTodos) setTodos(storedTodos)
  },[])

  //Called when the DOM has changes
  useEffect(() => {
    localStorage.setItem(LOCAL_STORAGE_KEY, JSON.stringify(todos)) 
    /*The first parameter is the name of the key that we wants to update/create. The second parameter contains the value that we want to assign to the key*/
    //JSON.stringify converts an object/value in a JSON string
  },[todos])

  function toggleTodo(id) {
    const newTodos=[...todos]
    const todo = newTodos.find(todo => todo.id === id)
    todo.complete = !todo.complete
    setTodos(newTodos)
  }

  function CreateTodo(e) {
    const name = TodoInputName.current.value //Prende il valore scritto nell'input
    if (name === '') return //Se non ho inserito nulla, ritorna
    //Aggiungo ai vecchi todos un nuovo todo
    setTodos(prevTodos => {
      return [...prevTodos, { id: uuidv4(), name: name, complete: false}] //Using uuidv4 to get unique id
    }) 
    TodoInputName.current.value = null //Clears the input field after clicling the button "Add Todo"
  }

  function DeleteTodos(e) {
    const newTodos = todos.filter(todo => !todo.complete)
    setTodos(newTodos)
  }
  
  return (
    <>
    <h1>TodoList</h1>
    <TodoList todos={todos} toggleTodo={toggleTodo}/>
    <div>
      <input ref={TodoInputName} type="text" /> 
      <button onClick={CreateTodo} >Add Todo</button> 
    </div>
    <button onClick={DeleteTodos}>Clear Complete</button>
    <div> {todos.filter(todo => !todo.complete).length} left todos </div>
    </>
  );
}

export default App;
