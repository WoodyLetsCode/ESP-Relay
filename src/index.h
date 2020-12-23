/*
 * More web UI HTML source arrays.
 * This file is auto generated, please don't make any changes manually.
 * Instead, see https://github.com/Aircoookie/WLED/wiki/Add-own-functionality#web-ui
 * to find out how to easily modify the web UI source!
 */ 

// Autogenerated from data/index.html, do not edit!!
const char PAGE_index[] PROGMEM = R"=====(<html lang="de">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP-Relay</title>
    <!-- Compiled and minified CSS -->
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/css/materialize.min.css">
    <!-- Compiled and minified JavaScript -->
    <script src="https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/js/materialize.min.js"></script>
    <style>
        table {
            border-collapse: initial;
            width: 800px;
            left: 50%;
            position: absolute;
            transform: translate(-50%);
        }

        td,
        th {
            text-align: center;
        }

        .tabs {
            left: 25%;
        }
    </style>
</head>

<body>

    <div id="crashWarning" class="modal">
        <div class="modal-content">
          <h4>Your device has crashed!</h4>
          <p>You device has crashed. Don't use invalid GPIO pins.</p>
        </div>
        <div class="modal-footer">
          <a class="modal-close waves-effect waves-green btn-flat" onclick="acceptCrash()">Okay</a>
        </div>
      </div>
              

    <div class="row">
        <div class="col s12">
            <ul class="tabs" id="tabs-swipe">
                <li class="tab col s3"><a class="active" href="#relays" onclick="loadRelays()">Relays</a></li>
                <li class="tab col s3"><a href="#settings" onclick="loadSettings()">Settings</a></li>
            </ul>
        </div>
        <div id="relays" class="col s12">
            <h1 class="center-align">Relays</h5>
                <br>
                <table id="relaysContent">

                </table>
        </div>
        <div id="settings" class="col s12" style="text-align: center;">
            <h1 class="center-align">Settings</h5>
                <p id="space"><b>Space:</b> 0/0 Bytes</p><br>
                <div id="relayInput" class="row"
                    style="width: 800px; left: 50%; position: absolute; transform: translate(-50%);">
                    <div class="input-field col s6">
                        <input id="relayName1" type="text" class="validate">
                        <label for="relayName1">Relay name</label>
                    </div>
                    <div class="input-field col s3">
                        <input id="relayPin1" type="number" class="validate">
                        <label for="relayPin1">Pin</label>
                    </div>
                    <div class="input-field col s3">
                        <select id="relayType1">
                            <option value="low">Low Level Trigger</option>
                            <option value="high">High Level Trigger</option>
                        </select>
                        <label>Relay type</label>
                    </div>
                    <button class="btn waves-effect waves-light" id="saveButton">Save</button>
                </div>
        </div>
    </div>

</body>

<script>
    M.AutoInit();
    var instance = M.Tabs.getInstance(document.getElementById("tabs-swipe"));
    loadRelays();
    checkCrash();

    function loadRelays() {
        // Get settings from json
        var xhr = new XMLHttpRequest();
        xhr.open('GET', '/json', true);
        xhr.onload = function () {
            console.log(xhr.response);
            if (xhr.response == "null") {
                document.getElementById("relaysContent").innerHTML = "<tr><td><br><a class=\"waves-effect waves-light btn-large lime accent-4\" id=\"addRelay\">Add relay</a></td></tr>";
                document.getElementById("addRelay").addEventListener("click", function () { instance.select('settings'); });
            } else {
                var json = JSON.parse(xhr.response);
                document.getElementById("relaysContent").innerHTML = "<tr><th>Toggle</th><th>Switch</th></tr>";
                for (let index = 0; index < json.length; index++) {
                    const element = json[index];
                    document.getElementById("relaysContent").innerHTML += "<tr><td><br><a class=\"waves-effect waves-light btn-large\" id=\"r" + (index + 1) + "\" onclick=\"toggleRelay(" + index + ")\">" + element["name"] + "</a></td><td><div class=\"switch\"><label>Off<input type=\"checkbox\" id=\"s" + (index + 1) + "\" onclick=\"switchRelay(" + index + ")\"><span class=\"lever\"></span>On</label></div></td></tr>";
                }
            }
        };
        xhr.send();
    }

    var numRelays = 1;
    document.getElementById("relayName1").addEventListener("input", newRelayInput);
    document.getElementById("saveButton").addEventListener("click", saveSettings);

    function newRelayInput() {
        console.log("newRelayInput()");
        if (document.getElementById("relayName" + numRelays).value != "") {
            appendRelayInputFields();
            moveButton();
            document.getElementById("relayName" + (numRelays - 1)).removeEventListener("input", newRelayInput);
            document.getElementById("relayName" + (numRelays - 1)).addEventListener("input", checkEmpty);
            document.getElementById("relayName" + numRelays).addEventListener("input", newRelayInput);
        }
    }

    function appendRelayInputFields() {
        numRelays++;
        console.log("numRelays: " + numRelays);

        var divName = document.createElement("div");
        divName.setAttribute("class", "input-field col s6");
        var inputName = document.createElement("input");
        inputName.setAttribute("id", "relayName" + numRelays);
        inputName.setAttribute("type", "text");
        inputName.setAttribute("class", "validate");
        var labelName = document.createElement("label");
        labelName.setAttribute("for", "relayName" + numRelays);
        labelName.innerText = "Relay name";
        divName.appendChild(inputName);
        divName.appendChild(labelName);

        var divPin = document.createElement("div");
        divPin.setAttribute("class", "input-field col s3");
        var inputPin = document.createElement("input");
        inputPin.setAttribute("id", "relayPin" + numRelays);
        inputPin.setAttribute("type", "number");
        inputPin.setAttribute("class", "validate");
        var labelPin = document.createElement("label");
        labelPin.setAttribute("for", "relayPin" + numRelays);
        labelPin.innerText = "Pin";
        divPin.appendChild(inputPin);
        divPin.appendChild(labelPin);

        var divSelect = document.createElement("div");
        divSelect.setAttribute("class", "input-field col s3");
        var selectRelayType = document.createElement("select");
        selectRelayType.setAttribute("id", "relayType" + numRelays);
        var selectOption1 = document.createElement("option");
        selectOption1.setAttribute("value", "low");
        selectOption1.innerText = "Low Level Trigger";
        var selectOption2 = document.createElement("option");
        selectOption2.setAttribute("value", "high");
        selectOption2.innerText = "High Level Trigger";
        var labelSelect = document.createElement("label");
        labelSelect.innerText = "Relay type";
        selectRelayType.appendChild(selectOption1);
        selectRelayType.appendChild(selectOption2);
        divSelect.appendChild(selectRelayType);
        divSelect.appendChild(labelSelect);

        relayInput.appendChild(divName);
        relayInput.appendChild(divPin);
        relayInput.appendChild(divSelect);

        M.AutoInit();
    }

    function moveButton() {
        var button = document.getElementById("saveButton");
        document.getElementById("saveButton").parentNode.removeChild(document.getElementById("saveButton"));
        relayInput.appendChild(button);
    }

    function checkEmpty() {
        for (let index = 1; index < numRelays; index++) {
            if (document.getElementById("relayName" + index).value == "") {
                for (let i = numRelays; i > index; i--) {
                    numRelays--;
                    removeParentNode("relayName" + i);
                    removeParentNode("relayPin" + i);
                    // remove select element
                    let element = document.getElementById("relayType" + i).parentNode.parentNode;
                    element.parentNode.removeChild(element);
                }
                document.getElementById("relayName" + index).addEventListener("input", newRelayInput);
            }

        }
    }

    function removeParentNode(elementId) {
        // Removes an ParentNode element from the document
        let element = document.getElementById(elementId).parentNode;
        element.parentNode.removeChild(element);
    }

    function loadSettings() {
        loadSpace();
        // Get settings from json
        var xhr = new XMLHttpRequest();
        xhr.open('GET', '/json', true);
        xhr.onload = function () {
            console.log(xhr.response);
            if (xhr.response != "null") {
                var json = JSON.parse(xhr.response);
                for (let index = 0; index < json.length; index++) {
                    const element = json[index];
                    newRelayInput();
                    document.getElementById("relayName" + (index + 1)).value = element["name"];
                    document.getElementById("relayPin" + (index + 1)).value = element["pin"];
                }
                newRelayInput();
                M.updateTextFields();
            }
        };
        xhr.send();
    }

    function loadSpace() {
        var xhr = new XMLHttpRequest();
        xhr.open('GET', '/info', true);

        xhr.onload = function () {
            var json = JSON.parse(xhr.response);
            document.getElementById("space").innerHTML = "<b>Space:</b> " + json["relays"]["Memory Usage"] + "/" + json["relays"]["Capacity"] + " Bytes";
        };

        xhr.send();
    }

    function saveSettings() {
        var data = [];
        for (let index = 0; index < (numRelays - 1); index++) {
            var obj = { "name": document.getElementById("relayName" + (index + 1)).value, "pin": parseInt(document.getElementById("relayPin" + (index + 1)).value), "Low Level Trigger": (document.getElementById("relayType" + (index + 1)).value === "low") };
            data[index] = obj;
        }
        console.log(data);
        var json = JSON.stringify(data);

        var xhr = new XMLHttpRequest();
        xhr.open("POST", '/json', true);
        //Send the proper header information along with the request
        xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
        xhr.onreadystatechange = function () { // Call a function when the state changes.
            if (this.readyState === XMLHttpRequest.DONE && this.status === 200) {
                loadSpace();
            }
        }
        xhr.send("json=" + json);
    }

    function toggleRelay(relay) {
        var xhr = new XMLHttpRequest();
        xhr.open('GET', '/toggle?r=' + relay, true);
        xhr.send();
    }

    function switchRelay(relay) {
        var xhr = new XMLHttpRequest();
        xhr.open('GET', '/switch?r=' + relay + '&on=' + document.getElementById("s" + (relay + 1)).checked, true);
        xhr.send();
    }

    // checks if device has crashed
    function checkCrash() {
        let xhr = new XMLHttpRequest();
        xhr.open('GET', '/info', true);

        xhr.onload = function () {
            var json = JSON.parse(xhr.response);
            if (json["crash"]["crash"] === true) {
                let instance = M.Modal.getInstance(document.getElementById("crashWarning"));
                instance.open();
            }
        };

        xhr.send();
    }

    function acceptCrash() {
        let xhr = new XMLHttpRequest();
        xhr.open('GET', '/crash');
        xhr.send();
    }
</script>

</html>)=====";

