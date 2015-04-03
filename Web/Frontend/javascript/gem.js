(function() {
    const gemID = getQueryParams()["id"];

    var request = new XMLHttpRequest();
    request.open("GET", "http://127.0.0.1:8080/gem/" + gemID + "/show.json");
    request.send();
    request.onload = function(e) {
        const dailies = JSON.parse(request.responseText);
        displayDailiesGraph(dailies);
    }

    function displayDailiesGraph(dailies) {
        var data = {
            labels: [],
            datasets: [{
                label: "example",
                fillColor: "rgba(220,220,220,0.2)",
                strokeColor: "rgba(220,220,220,1)",
                pointColor: "rgba(220,220,220,1)",
                pointStrokeColor: "#fff",
                pointHighlightFill: "#fff",
                pointHighlightStroke: "rgba(220,220,220,1)",
                data: []
            }]
        };
        dailies.forEach(function (daily) {
            data.labels.push(daily.date);
            data.datasets[0].data.push(daily.downloads);
        });

        const ctx = document.getElementById("dailiesChart").getContext("2d");
        const dailiesChart = new Chart(ctx).Line(data);
    }

    function getQueryParams() {
        const rawParams = window.location.search.substring(1);
        var params = {};

        // Exit early if posible
        if (rawParams.length === 0) {
            return params;
        }

        var moreParamsExist = true;
        var startPosition = 0;
        while (moreParamsExist) {
            var nextAmpersand = rawParams.indexOf("&", startPosition);

            if (nextAmpersand === -1) {
                nextAmpersand = rawParams.length;
                moreParamsExist = false;
            }

            const rawParam = rawParams.substring(startPosition, nextAmpersand);
            const result = rawParam.split("=");
            params[result[0]] = result[1];

            startPosition = nextAmpersand + 1;
        }

        return params;
    }
})();

