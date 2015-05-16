/* Begin Utils */
var urlParams = (function(a) {
    if (a == "") return {};
    var b = {};
    for (var i = 0; i < a.length; ++i)
    {
        var p=a[i].split('=', 2);
        if (p.length == 1)
            b[p[0]] = "";
        else
            b[p[0]] = decodeURIComponent(p[1].replace(/\+/g, " "));
    }
    return b;
})(window.location.search.substr(1).split('&'));

function calcOpacity(val) {
    var minOpacity = 0.2;
    var maxOpacity = 0.75;

    return (maxOpacity - minOpacity) * val/100.0 + minOpacity;
}

/* End Utils */


/* Begin Main */
// For diagram (and table)
if (typeof urlParams["MindMuscle"] !== "undefined") {
    var val = Math.min(99, Math.max(0, parseInt(urlParams["MindMuscle"])));
    document.querySelector("section.diagram .overall").innerHTML = val;
}

if (typeof urlParams["Level1Avg"] !== "undefined") {
    var val = Math.min(99, Math.max(0, parseInt(urlParams["Level1Avg"])));
    document.querySelector("section.diagram .circle.level1 text").innerHTML = val;
    document.querySelector("section.diagram .circle.level1 circle").setAttribute("fill-opacity", calcOpacity(val));

    document.querySelector("section.table.level1 td.average").innerHTML = val;
}
if (typeof urlParams["Level2Avg"] !== "undefined") {
    var val = Math.min(99, Math.max(0, parseInt(urlParams["Level2Avg"])));
    document.querySelector("section.diagram .circle.level2 text").innerHTML = val;
    document.querySelector("section.diagram .circle.level2 circle").setAttribute("fill-opacity", calcOpacity(val));

    document.querySelector("section.table.level2 td.average").innerHTML = val;
}
if (typeof urlParams["Level3Avg"] !== "undefined") {
    var val = Math.min(99, Math.max(0, parseInt(urlParams["Level3Avg"])));
    document.querySelector("section.diagram .circle.level3 text").innerHTML = val;
    document.querySelector("section.diagram .circle.level3 circle").setAttribute("fill-opacity", calcOpacity(val));

    document.querySelector("section.table.level3 td.average").innerHTML = val;
}


// For table (only)
if (typeof urlParams["Level1Highest"] !== "undefined") {
    var val = Math.min(99, Math.max(0, parseInt(urlParams["Level1Highest"])));
    document.querySelector("section.table.level1 td.highest").innerHTML = val;
}
if (typeof urlParams["Level2Highest"] !== "undefined") {
    var val = Math.min(99, Math.max(0, parseInt(urlParams["Level2Highest"])));
    document.querySelector("section.table.level2 td.highest").innerHTML = val;
}
if (typeof urlParams["Level3Highest"] !== "undefined") {
    var val = Math.min(99, Math.max(0, parseInt(urlParams["Level3Highest"])));
    document.querySelector("section.table.level3 td.highest").innerHTML = val;
}

if (typeof urlParams["Level1Score"] !== "undefined") {
    var val = Math.min(99, Math.max(0, parseInt(urlParams["Level1Score"])));
    document.querySelector("section.table.level1 td.score").innerHTML = val;
}
if (typeof urlParams["Level2Score"] !== "undefined") {
    var val = Math.min(99, Math.max(0, parseInt(urlParams["Level2Score"])));
    document.querySelector("section.table.level2 td.score").innerHTML = val;
}
if (typeof urlParams["Level3Score"] !== "undefined") {
    var val = Math.min(99, Math.max(0, parseInt(urlParams["Level3Score"])));
    document.querySelector("section.table.level3 td.score").innerHTML = val;
}
/* End Main */