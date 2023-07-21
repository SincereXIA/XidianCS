const {BrowserWindow} = require('electron').remote
const path = require('path')
//require('cheerio')
$ = require('jquery')

const queryBtn = document.getElementById('queryByID')
const rpc =  require('./../../rpc.js')

queryBtn.addEventListener('click', (event) => {
  id = document.getElementById('ID').value
  console.log(id)
  rpc.queryByID(id, printtable);
})

function printtable (book) {
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
  $('#result').empty()
  $('#result').append(table)
}