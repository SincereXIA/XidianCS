import GrpcProto.BookManager;
import GrpcProto.BookManagerGrpc;
import SincereXIA.distribrpc.book.Book;
import SincereXIA.distribrpc.book.BookID;
import SincereXIA.distribrpc.book.BookName;
import SincereXIA.distribrpc.book.Request;
import io.grpc.Server;
import io.grpc.ServerBuilder;
import io.grpc.stub.StreamObserver;
import java.io.IOException;
import java.util.logging.Logger;


public class BookManagerServer {

    private Server server;
    private static final Logger logger =  Logger.getLogger("main");

    private void start() throws IOException {
        /* The port on which the server should run */
        int port = 50051;
        server = ServerBuilder.forPort(port).addService(new BookManager()).build().start();
        System.out.println("**** 服务成功启动");
        Runtime.getRuntime().addShutdownHook(new Thread() {
            @Override
            public void run() {
                // Use stderr here since the logger may have been reset by its
                // JVM shutdown hook.
                System.err.println("*** shutting down gRPC server since JVM is shutting down");
                BookManagerServer.this.stop();
                System.err.println("*** server shut down");
            }
        });
    }

    private void stop() {
        if (server != null) {
            server.shutdown();
        }
    }

    /**
     * Await termination on the GreeterServer thread since the grpc library uses daemon
     * threads.
     */
    private void blockUntilShutdown() throws InterruptedException {
        if (server != null) {
            server.awaitTermination();
        }
    }

    /**
     * Main launches the server from the command line.
     */
    public static void main(String[] args) throws IOException, InterruptedException {
        final BookManagerServer server = new BookManagerServer();
        server.start();
        server.blockUntilShutdown();
    }


}
