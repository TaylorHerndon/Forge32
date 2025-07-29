function appendHtmlIntoDiv(divId, htmlFilePath) {
    fetch(htmlFilePath)
        .then(response => response.text())
        .then(data => {
            document.getElementById(divId).insertAdjacentHTML('beforeend', data);
        })
        .catch(error => {
            console.error('Error loading HTML:', error);
        });
}

function updateDynamicContent() {
    fetch("/dynamic-content")
        .then(response => response.text())
        .then(data => {
            document.getElementById("dynamic-content").innerHTML = "";
            jsonObject = JSON.parse(data);
            Object.keys(jsonObject).forEach(key => {
                // Iterate through all nodes sent in JSON format.
                var card = constructCard(key, jsonObject[key]);
                document.getElementById("dynamic-content").appendChild(card);
            });
        })
        .catch(error => {
            console.error('Error fetching dynamic content:', error);
        });
}

function constructCard(title, capabilities) {
    //Title = string, content = JSON object
    var card = document.createElement('div');
    card.id = title;
    card.className = "card";
    var titleP = document.createElement('p');
    titleP.className = "card-title";
    titleP.innerHTML = title;
    card.append(titleP);

    Object.entries(capabilities).forEach(([key, value]) => {
        newElement = "";
        if (value.type == "sensor" && value.dataType == "bool") {
            newElement = `
            <div class="control-container">
                <p>${key}</p>
                <div class="bool-indicator" data-value="0"></div>
            </div>`;
        }
        else if (value.type == "sensor" && (value.dataType == "int" || value.dataType == "float")) {
            newElement = `
            <div class="control-container">
                <p>${key}</p>
                <p class="digit-display">-.----</p>
            </div>`;
        }
        else if (value.type == "control" && value.dataType == "bool") {
            newElement = `
            <div class="control-container">
                <p>${key}</p>
                <button class="button-green">Bool Control</button>
            </div>`;
        }
        else if (value.type == "control" && (value.dataType == "int" || value.dataType == "float")) {
            newElement = `
            <div class="control-container">
                <p>${key}</p>
                <input id="slider" type="range" class="numeric-slider" min="${value.range[0]}" max="${value.range[1]}" value="${value.range[0]}">
            </div>`;
        }
        card.insertAdjacentHTML('beforeend', newElement);
    });

    return card;
}

function connectButtonClick() {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "/connect_click", true); // Send a GET request to /connect_click
    xhr.send();
}

function disconnectButtonClick() {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "/disconnect_click", true); // Send a GET request to /disconnect_click
    xhr.send();
}

function updateCurrentTime() {
    fetch("/current-time").then(response => response.text()).then(data => {
        document.getElementById('current-time').innerHTML = data;
    })
}