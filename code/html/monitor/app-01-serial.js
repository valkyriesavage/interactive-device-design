// Mac OS X example for reading serial data in node.js and sending it to a browser via websockets
// Depends on the Express web framework, socket.io library and node-serialport library:
// npm install express socket.io serialport

// change this to point to your serial port
var portName = "/dev/tty.usbmodem411";

var serialport = require("serialport");
var SerialPort = serialport.SerialPort;

// set up parser to read line-by-line
var sp = new SerialPort(portName,{ 
    parser: serialport.parsers.readline("\n") 
});

//callback: report data, print to console
sp.on("data", function (data) {
    console.log("here: "+data);
});