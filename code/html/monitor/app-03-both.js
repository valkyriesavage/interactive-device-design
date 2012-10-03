// Mac OS X example for pushing serial data to connected brower(s) via socket.io
// Depends on the Express 2.x web framework, socket.io and node-serialport:
// npm install express socket.io serialport

// express initialization
var app = require('express').createServer()
  , io = require('socket.io').listen(app);

// serial port initialization
// change this to point to your serial port
var portName = "/dev/tty.usbmodem411";
var serialport = require("serialport");
var SerialPort = serialport.SerialPort;

// set up parser to read line-by-line
var sp = new SerialPort(portName,{ 
    parser: serialport.parsers.readline("\n") 
});

// set up web server on port 8080
app.listen(8080);
app.get('/', function (req, res) {
  res.sendfile(__dirname + '/index.html');
});

// when a new socket.io connection is made - do nothing
io.sockets.on('connection', function (socket) {
});

//serial callback: fwd data to all socket clients
sp.on("data", function (data) {
	fields = data.split(" ");
	io.sockets.clients().forEach(function (socket) {
		socket.emit('a2d',{a0:fields[0],a1:fields[1]});	
	});	
});
