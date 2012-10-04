// express initialization
var app = require('express').createServer()
  , io = require('socket.io').listen(app);

// serial port initialization
var serialport = require("serialport");
var SerialPort = serialport.SerialPort;
var sensingPortName = "/dev/tty.usbserial-FTFOM7O3";
var actuationPortName = "/dev/tty.usbmodem411";

// set up parser to read line-by-line
var sp = new SerialPort(sensingPortName,{ 
    parser: serialport.parsers.readline("\n") 
});


// set up web server on port 8080
app.listen(8080);
app.get('/', function (req, res) {
  res.sendfile(__dirname + '/client.html');
});

// when a new socket.io connection is made - set er up
io.sockets.on('connection', function (socket) {
    socket.on('water', function(data) {
      console.log('water it!');
      sp.write(new Buffer([0x01]));
    });
});

//sensing serial callback: fwd data to all socket clients
sp.on('data', function (data) {
	io.sockets.clients().forEach(function (socket) {
		socket.emit('a2d',{a0:data});	
	});	
});
