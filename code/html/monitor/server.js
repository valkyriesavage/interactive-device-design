// express initialization
var app = require('express').createServer()
  , io = require('socket.io').listen(app);

// serial port initialization
var serialport = require("serialport");
var SerialPort = serialport.SerialPort;
var sensingPortName = "/dev/tty.usbmodem411";
var actuationPortName = "/dev/tty.usbmodem411";

// set up parser to read line-by-line
var ssp = new SerialPort(sensingPortName,{ 
    parser: serialport.parsers.readline("\n") 
});
var asp = new SerialPort(sensingPortName,{ 
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

//sensing serial callback: fwd data to all socket clients
ssp.on("data", function (data) {
	fields = data.split(" ");
	io.sockets.clients().forEach(function (socket) {
		socket.emit('a2d',{a0:fields[0],a1:fields[1]});	
	});	
});

//socket connection callback: fwd data to actuation serial port
io.sockets.on('data', function(data) {
        gotData = true;
        asp.write(new Buffer([0x01]));
});
