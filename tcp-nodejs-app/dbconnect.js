var mysql = require('mysql');

var con = mysql.createConnection({
  host: "localhost",
  user: "viettelapp",
  password: "123456",
  database: "viettelapp"
});

con.connect(function(err){
if(!err) {
    console.log("Database is connected ... nn");
} else {
    console.log("Error connecting database ... nn");
}
});

exports.login = function(usrname,usrpwd,cb){
    con.query("SELECT * FROM vtuser WHERE username = ? and password = ?",[ usrname, usrpwd ], cb);
}

exports.checkUserPms = function(usrId,cb){
    con.query("SELECT pmsId FROM usePpermission WHERE userId = ?",[ usrId ], cb);
}
