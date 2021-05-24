package GrpcProto;

import SincereXIA.distribrpc.book.*;
import db.HibernateUtil;
import io.grpc.stub.StreamObserver;
import org.hibernate.Session;
import org.hibernate.Transaction;
import org.hibernate.query.Query;

import java.util.List;
import java.util.logging.Logger;

public class BookManager extends BookManagerGrpc.BookManagerImplBase{
    private static final Logger logger =  Logger.getLogger("main");
    Session session = HibernateUtil.getSessionFactory().openSession();

    Book getBookByID(int id){
        //session.beginTransaction();
        dbBook dbook = session.get(dbBook.class,id);
        BookID bookID = BookID.newBuilder().setId(dbook.getId()).build();
        BookName bookName = BookName.newBuilder().setName(dbook.getBookName()).build();
        Book book = Book.newBuilder().setBookID(bookID).setBookAuthor(dbook.getBookAuthor())
                .setBookName(bookName).build();
        return book;
    }

    Book B2B(dbBook dbook){
        BookID bookID = BookID.newBuilder().setId(dbook.getId()).build();
        BookName bookName = BookName.newBuilder().setName(dbook.getBookName()).build();
        return Book.newBuilder().setBookID(bookID).setBookAuthor(dbook.getBookAuthor())
                .setBookName(bookName).build();
    }
    dbBook B2B(Book book){
        dbBook db = new dbBook();
        db.setBookName(book.getBookName().getName());
        db.setBookAuthor(book.getBookAuthor());
        db.setBookInfo(book.getBookInfo());
        return db;
    }


    BookList getBooksByName(String name){
        Query query = session.createQuery("from dbBook as b where b.bookName like :bookname");
        query.setString("bookname","%"+name+"%");
        List<dbBook> result = query.list();

        BookList.Builder bookListb = BookList.newBuilder();
        for (dbBook dbk:
             result) {
            bookListb.addBook(B2B(dbk));
        }
        return bookListb.build();
    }

    boolean insertBook(dbBook book){
        try{
            Transaction tx =  session.beginTransaction();
            session.saveOrUpdate(book);
            tx.commit();
            return true;
        }catch (Exception e){
            return false;
        }finally {
            //session.close();
        }

    }
    boolean deleteBook(Integer id){
        try{
            dbBook dbook = session.get(dbBook.class,id);
            Transaction tx =  session.beginTransaction();
            session.delete(dbook);
            tx.commit();
            return true;
        }catch (Exception e){
            return false;
        }finally {
            //session.close();
        }
    }

    @Override
    public void queryByID(Request request, StreamObserver<Book> responseObserver) {
        int id = request.getBookID().getId();
        responseObserver.onNext(getBookByID(id));
        logger.info("queryByID: " + id + "Finish");
        responseObserver.onCompleted();
    }

    @Override
    public void queryByName(Request request, StreamObserver<BookList> responseObserver) {
        String bookname = request.getBookName().getName();
        responseObserver.onNext(getBooksByName(bookname));
        logger.info("queryByName: "+ bookname+ " finish");
        responseObserver.onCompleted();
    }

    @Override
    public void add(Request request, StreamObserver<Reply> responseObserver) {
        Book book = request.getBook();
        Reply r;
        if(insertBook(B2B(book))){
            r = Reply.newBuilder().setStatus(200).setMsg(book.getBookName().getName()+"添加成功").build();
        }else{
            logger.info("Add ERROR");
            r = Reply.newBuilder().setStatus(400).setMsg(book.getBookName().getName()+"添加失败").build();
        }
        logger.info("Add finish");
        responseObserver.onNext(r);
        responseObserver.onCompleted();
    }

    @Override
    public void delete(Request request, StreamObserver<Reply> responseObserver) {
        BookID bookID  = request.getBookID();
        Integer id = bookID.getId();
        Reply r;
        if(deleteBook(id)){
            logger.info("del a book finish success");
            r = Reply.newBuilder().setStatus(200).setMsg("删除成功").build();
        }else{
            logger.info("del a book error");
            r = Reply.newBuilder().setStatus(400).setMsg("删除失败").build();
        }
        responseObserver.onNext(r);
        responseObserver.onCompleted();
    }
}
