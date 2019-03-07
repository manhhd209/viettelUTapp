const net = require('net');
const port = 7070;
const host = '127.0.0.1';
var db = require('./dbconnect');


const server = net.createServer();
server.listen(port, host, () => {
    console.log('TCP Server is running on port ' + port + '.');
});



server.on('connection', function(sock) {
    console.log('CONNECTED: ' + sock.remoteAddress + ':' + sock.remotePort);
    sock.setEncoding('utf8');
    sock.on('data', function(data) {
        console.log('DATA ' + sock.remoteAddress + ': ' + data);
        // Write the data back to all the connected, the client will receive it as data from the server
        jsonAnalyze(data,sock);
    });

    // Add a 'close' event handler to this instance of socket
    sock.on('close', function(data) {
        // let index = sockets.findIndex(function(o) {
        //     return o.remoteAddress === sock.remoteAddress && o.remotePort === sock.remotePort;
        // })
        // if (index !== -1) sockets.splice(index, 1);
        console.log('CLOSED: ' + sock.remoteAddress + ' ' + sock.remotePort);
    });
});

function jsonAnalyze(data,sock){
  json = JSON.parse(data);
  if(json.type == "logininfo"){
    checkLogin(json,sock);
  }
}

function checkLogin(data,sock){
  let userId = data.usrname;
  let userPwd = data.usrpwd;
  db.login(userId,userPwd,function (err, result, fields){
    if (err) throw err;
    if(typeof result !== 'undefined' && result.length > 0){
      let res = {};
      res.type = 'login';
      res.loginstt = 'loginOk';
      res.name = result[0].displayname;
      db.checkUserPms(result[0].userid,function (err, result, fields){
        if (err) throw err;
        let pms = [];
        for (var i = 0; i < result.length; i++) {
          pms.push(result[i].pmsId)
        }
        res.permission = pms;
        console.log(res);
        sock.write(JSON.stringify(res));
      });
    }else{
      let res = {};
      res.type = 'login';
      res.loginstt = 'loginFail';
      console.log(res);
      sock.write(JSON.stringify(res));
    }
  });
  return true;
}

function findUserPermission(userId){
  db.checkUserPms(userId,function (err, result, fields){
    if (err) throw err;
    let pms = [];
    for (var i = 0; i < result.length; i++) {
      pms.push(result[i].pmsId)
    }
    return pms;
  });
}
