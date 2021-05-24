var grpc = require('grpc');
var PROTO_PATH = __dirname + '\\protos\\books.proto';
var protoLoader = require('@grpc/proto-loader');
var packageDefinition = protoLoader.loadSync(
    PROTO_PATH,
    {keepCase: true,
        longs: String,
        enums: String,
        defaults: true,
        oneofs: true
    });
const library = grpc.loadPackageDefinition(packageDefinition).library;
var bookManager = new library.BookManager('disk.sumblog.cn:50051',
    grpc.credentials.createInsecure());

/**
 * 通过 ID 值来获取书籍
 * @param id 书的编号 一个整数
 * @param callback
 */
function queryByID(id, callback) {
    function _(err, book) {
        if (err) {
            console.log(err);
        } else {
            callback(book);
        }
    }
    return bookManager.queryByID({"bookID": {'id': id}},  _);
}

function queryByName(bookname, callback) {
    return bookManager.queryByName({"bookName":{'name':bookname}}, function (err, books) {
        if (err){
            console.log(err);
        } else {
            callback(books.book)
        }
    })
}

function add(request, callback) {
    return bookManager.add(request, function (err, msg) {
        if (err){
            console.log(err);
        }else {
            callback(msg);
        }
    })
}

function del(request, callback){
    return bookManager.delete(request, function (err, msg) {
        if (err){
            console.log(err);
        }else {
            callback(msg);
        }
    })
}

module.exports = {
    queryByID,
    queryByName,
    add,
    del
}
