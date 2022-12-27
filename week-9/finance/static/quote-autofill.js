symbol = document.querySelector("#symbol");
autoCompleteEls = [];
symbol.addEventListener("input", () => {
    autoComplete = document.querySelector(".auto-complete")
    while (autoComplete.lastChild) {
        autoComplete.removeChild(autoComplete.lastChild);
    }
    if (symbol.value == '') return;

    fetch('/ticker', {
        method: 'POST',
        headers: {
            'Accept': 'application/json',
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ "ticker":  symbol.value})
    })
    .then(response => response.json())
    .then(data => {
        data.forEach((val) => {
            itemEl = document.createElement("li")
            element = document.createElement("button")
            itemEl.appendChild(element)
            element.innerHTML = val.ticker
            element.addEventListener('click', () => {console.log('click'); symbol.value = val.ticker; symbol.dispatchEvent(new Event('input'))})
            autoCompleteEls.push(val.ticker)
            autoComplete.appendChild(itemEl)
        })
    })

})
/*
symbol.addEventListener("blur", () => {
    setTimeout(()=> {
        autoComplete = document.querySelector(".auto-complete")
        while (autoComplete.lastChild) {
            autoComplete.removeChild(autoComplete.lastChild);
        }
    }, 10)
})*/

symbol.addEventListener("focus", () => {
    symbol.dispatchEvent(new Event("input"))
})
