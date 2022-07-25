function angleToArc(angle)
{
    return Math.PI * angle / 180;
}

function getLineCenter(x1, y1, x2, y2)
{
    var p = {};
    p.x = (x1 + x2) / 2;
    p.y = (y1 + y2) / 2;
    return p;
}

function centerToLeftTop(x, y, w, h)
{
    var p = {};
    p.x = x - (w / 2);
    p.y = y - (h / 2);
    return p;
}

function leftTopToCenter(x, y, w, h)
{
    var p = {};
    p.x = x + (w / 2);
    p.y = y + (y / 2);
    return p;
}
