import React, {useState, useEffect} from 'react';
import './App.css';
import Currency from './Currency';

const URL = 'https://api.exchangeratesapi.io/latest'

function App() {
  const [CurrencyOptions, SetCurrencyOptions] = useState([]) //State of the currency from the URL
  const [FromCurrency, setFromCurrency] = useState() //State of the first currency drop down list
  const [ToCurrency, setToCurrency] = useState() //State of the second currency drop down list
  const [Rate, SetRate] = useState() //State of the rate to apply
  const [amount, setAmount] = useState(1) //State of the number of money
  const [amountInFromCurrency, setAmountInFromCurrency] = useState(true) //State that controls which input number take

  //Calculating the amount
  let toAmount, fromAmount
  if (amountInFromCurrency) { //Controls if is the first input field that has changed
    fromAmount = amount
    toAmount = amount * Rate
  } else { //Controls if is the second input field that has changed
    toAmount = amount
    fromAmount = amount / Rate
  }

//SetUP state on refresh
 useEffect(() => {
  fetch(URL)
    .then(response => response.json())
    .then(data => {
      const tocurrency = Object.keys(data.rates)[0]
      SetCurrencyOptions([data.base, ...Object.keys(data.rates)])
      setFromCurrency(data.base)
      setToCurrency(tocurrency)
      SetRate(data.rates[tocurrency])
    })
 },[])

 //SetUP concurrency on concurrency change in dropdownlist
 useEffect(() => {
  if (FromCurrency != null && ToCurrency != null) {
    fetch(`${URL}?base=${FromCurrency}&symbols=${ToCurrency}`)
      .then(res => res.json())
      .then(data => SetRate(data.rates[ToCurrency]))
  }
}, [FromCurrency, ToCurrency])

//When the amount change, set up the amount state and the input change state
function handleFromAmountChange(e) {
  setAmount(e.target.value)
  setAmountInFromCurrency(true)
}
//When the amount change, set up the amount state and the input change state
function handleToAmountChange(e) {
  setAmount(e.target.value)
  setAmountInFromCurrency(false)
}

  return (
  <>
  <div>Currency Exchange</div>
  <Currency 
  currencyOptions={CurrencyOptions} 
  selectedCurrency={FromCurrency}
  onChangeCurrency={e => setFromCurrency(e.target.value)}
  onChangeAmount={handleFromAmountChange}
  amount={fromAmount}
  />
  <div className="equals">=</div>
  <Currency 
  currencyOptions={CurrencyOptions} 
  selectedCurrency={ToCurrency}
  onChangeCurrency={e => setToCurrency(e.target.value)}
  onChangeAmount={handleToAmountChange}
  amount={toAmount}
  />
  </>
  );
}

export default App;
