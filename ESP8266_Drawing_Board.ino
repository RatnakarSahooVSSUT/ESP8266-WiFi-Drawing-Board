#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SPI.h>
#include <Ucglib.h>

Ucglib_ILI9341_18x240x320_HWSPI ucg(
  D4,
  D8,
  D0
);

ESP8266WebServer server(80);

const char* ssid = "ESP_DrawBoard";
const char* password = "12345678";

String receivedData = "";

const char webpage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>ESP Draw Board</title>

<style>
body{
  text-align:center;
  font-family:Arial;
}

canvas{
  border:2px solid black;
  touch-action:none;
}

button{
  padding:10px;
  margin:5px;
}
</style>
</head>

<body>

<h2>ESP Draw Board</h2>

<canvas id="canvas" width="240" height="320"></canvas>

<br>

<button onclick="setColor('red')">Red</button>
<button onclick="setColor('green')">Green</button>
<button onclick="setColor('blue')">Blue</button>
<button onclick="setColor('black')">Black</button>

<br>

<button onclick="clearCanvas()">Clear</button>
<button onclick="sendData()">SEND TO ESP</button>

<script>

let canvas = document.getElementById('canvas');
let ctx = canvas.getContext('2d');

let drawing = false;
let color = "black";

let lastX = 0;
let lastY = 0;

let points = [];

ctx.lineCap = "round";
ctx.lineJoin = "round";

function setColor(c)
{
  color = c;
}

canvas.addEventListener('mousedown', start);
canvas.addEventListener('mousemove', draw);
canvas.addEventListener('mouseup', stop);
canvas.addEventListener('mouseleave', stop);

canvas.addEventListener('touchstart', startTouch);
canvas.addEventListener('touchmove', drawTouch);
canvas.addEventListener('touchend', stop);

function start(e)
{
  drawing = true;

  let rect = canvas.getBoundingClientRect();

  lastX = e.clientX - rect.left;
  lastY = e.clientY - rect.top;
}

function draw(e)
{
  if(!drawing) return;

  let rect = canvas.getBoundingClientRect();

  let x = e.clientX - rect.left;
  let y = e.clientY - rect.top;

  ctx.strokeStyle = color;
  ctx.lineWidth = 5;

  ctx.beginPath();
  ctx.moveTo(lastX,lastY);
  ctx.lineTo(x,y);
  ctx.stroke();

  points.push(
    Math.round(lastX)+","+
    Math.round(lastY)+","+
    Math.round(x)+","+
    Math.round(y)+","+
    color
  );

  lastX = x;
  lastY = y;
}

function stop()
{
  drawing = false;
}

function startTouch(e)
{
  e.preventDefault();

  drawing = true;

  let rect = canvas.getBoundingClientRect();

  lastX = e.touches[0].clientX - rect.left;
  lastY = e.touches[0].clientY - rect.top;
}

function drawTouch(e)
{
  e.preventDefault();

  if(!drawing) return;

  let rect = canvas.getBoundingClientRect();

  let x = e.touches[0].clientX - rect.left;
  let y = e.touches[0].clientY - rect.top;

  ctx.strokeStyle = color;
  ctx.lineWidth = 5;

  ctx.beginPath();
  ctx.moveTo(lastX,lastY);
  ctx.lineTo(x,y);
  ctx.stroke();

  points.push(
    Math.round(lastX)+","+
    Math.round(lastY)+","+
    Math.round(x)+","+
    Math.round(y)+","+
    color
  );

  lastX = x;
  lastY = y;
}

function clearCanvas()
{
  ctx.clearRect(0,0,240,320);

  points = [];
}

function sendData()
{
  fetch('/upload',
  {
    method:'POST',
    body:points.join(';')
  })
  .then(response => response.text())
  .then(data => alert(data));
}

</script>


</body>
</html>
)rawliteral";

void handleRoot()
{
  server.send_P(200,"text/html",webpage);
}

void handleUpload()
{
  String data = server.arg("plain");

  Serial.println("Drawing Received");

  ucg.clearScreen();

  int start = 0;

  while(start < data.length())
  {
    int end = data.indexOf(';', start);

    if(end == -1)
      end = data.length();

    String seg = data.substring(start, end);

    int p1 = seg.indexOf(',');
    int p2 = seg.indexOf(',', p1 + 1);
    int p3 = seg.indexOf(',', p2 + 1);
    int p4 = seg.indexOf(',', p3 + 1);

    if(p1>0 && p2>0 && p3>0 && p4>0)
    {
      int x1 = seg.substring(0,p1).toInt();
      int y1 = seg.substring(p1+1,p2).toInt();

      int x2 = seg.substring(p2+1,p3).toInt();
      int y2 = seg.substring(p3+1,p4).toInt();

      String col = seg.substring(p4+1);

      if(col == "red")
        ucg.setColor(0,0,255);

      else if(col == "green")
        ucg.setColor(0,255,0);

      else if(col == "blue")
        ucg.setColor(255,0,0);

      else
        ucg.setColor(255,255,255);

      ucg.drawLine(
        x1,
        y1,
        x2,
        y2
      );
    }

    start = end + 1;
  }

  server.send(
    200,
    "text/plain",
    "Displayed on TFT!"
  );
}

void setup()
{
  Serial.begin(115200);

  WiFi.softAP(ssid,password);

  ucg.begin(0);

  ucg.clearScreen();

  ucg.setColor(255,255,255);

  ucg.setFont(ucg_font_6x13_tr);

  ucg.setPrintPos(20,30);
  ucg.print("Waiting for drawing...");

  Serial.println();
  Serial.println("WiFi Started");

  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/",handleRoot);
  server.on("/upload",HTTP_POST,handleUpload);

  server.begin();

  Serial.println("Server Started");
}

void loop()
{
  server.handleClient();
}