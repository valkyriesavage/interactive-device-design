// Mac OS X example for updating browser data via socket.io
// Depends on the Express 2.x web framework, socket.io library:
// npm install express socket.io

var app = require('express').createServer()
  , io = require('socket.io').listen(app);

var a0=0, a1=0; // counters

// set up web server on port 8080
app.listen(8080);
app.get('/', function (req, res) {
  res.sendfile(__dirname + '/index.html');
});

// when a new socket.io connection is made - do nothing
io.sockets.on('connection', function (socket) {
});

//every second, send some data to all connected sockets
setInterval(function() {
	io.sockets.clients().forEach(function (socket) {
		socket.emit('a2d',{a0:a0++,a1:a1++});	
	});	
},1000);
