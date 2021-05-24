
const {BrowserWindow} = require('electron').remote
const path = require('path')
$ = require('jquery')

const queryBtn = document.getElementById('queryAllBook')
const rpc =  require('./../../rpc.js')
const addBtn = document.getElementById('addBook')
const delBtn = document.getElementById('delBook')

queryBtn.addEventListener('click', (event) => {
  rpc.queryByName("", printtable);
})

addBtn.addEventListener('click', (event) => {
  addBookName = document.getElementById('addBookName').value
  addBookAuthor = document.getElementById('addBookAuthor').value
  addBookInfo = document.getElementById('addBookInfo').innerHTML
  request = {
    'book':{'bookName': {'name': addBookName},'bookAuthor': addBookAuthor, 'bookInfo':addBookInfo},
    'userID':{'userName': usrID, 'userPwd': usrPSW}
  }
  rpc.add(request, function (msg) {
    document.getElementById('addStatus').innerText = msg.msg
  })
})



delBtn.addEventListener('click', (event) =>{
  function delrow(msg){
    queryBtn.click();
    delBtn.click();
  }
  function newdel(id){
    var del = document.createElement('td')
    delurl = document.createElement('a')
    delurl.innerText = '删除'
    delurl.addEventListener('click', (event) => {
      console.log(id)
      request = {
        'bookID':{'id': id},
        'userID':{'userName': usrID, 'userPwd': usrPSW}
      }
      rpc.del(request, delrow)
    })
    del.append(delurl)
    return del
  }
  th = document.createElement('th')
  th.innerHTML='操作'
  tr.append(th)
  $('tr#AllBookResult:first').append(th)
  $('tr').each(function (index, row) {
    if (index !== 0) {
      id = row.children[0].innerHTML
      console.log(id)
      row.append(newdel(id))
    }
  })
})

function printtable (books) {
  tr = document.createElement("tr")
  // tr.append(document.createElement('th'))
  th = document.createElement('th')
  th.innerHTML='ID'
  tr.append(th)
  th = document.createElement('th')
  th.innerHTML='书名'
  tr.append(th)
  th = document.createElement('th')
  th.innerHTML='作者'
  tr.append(th)
  th = document.createElement('th')
  th.innerHTML='简介'
  tr.append(th)
  table = document.createElement("table")
  table.append(tr)
  books.forEach(function (book) {
    row =  document.createElement("tr")
    id = document.createElement("td")
    id.append(book.bookID.id)
    bookname = document.createElement("td")
    bookname.append(book.bookName.name);
    author = document.createElement("td")
    author.append(book.bookAuthor);
    bookinfo = document.createElement("td")
    bookinfo.append(book.bookInfo);
    row.append(id, bookname, author, bookinfo)
    table.append(row)
  })
  $('#AllBookResult').empty()
  $('#AllBookResult').append(table)
}
var isLogged = false
var usrID
var usrPSW
document.getElementById('button-showBooks').addEventListener('click', function () {
  if(isLogged){
    return
  }
  const modalPath = path.join('file://', __dirname, '../../sections/library-manage/login.html')
  let win = new BrowserWindow({frame: false, width: 300, height:400})

  win.on('close', () => { win = null })
  win.loadURL(modalPath)
  win.once('ready-to-show', () => {
    win.show()
  })
})

const {ipcRenderer} = require("electron")
ipcRenderer.on('loginSucceeded-message',(event,arg) =>{
  document.getElementById('LoginWelcome').innerText = arg.usrID + "欢迎您！";
  isLogged = true
  usrID = arg.usrID
  usrPSW = arg.usrPSW
})

