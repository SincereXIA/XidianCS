package GrpcProto;

import static io.grpc.MethodDescriptor.generateFullMethodName;
import static io.grpc.stub.ClientCalls.asyncBidiStreamingCall;
import static io.grpc.stub.ClientCalls.asyncClientStreamingCall;
import static io.grpc.stub.ClientCalls.asyncServerStreamingCall;
import static io.grpc.stub.ClientCalls.asyncUnaryCall;
import static io.grpc.stub.ClientCalls.blockingServerStreamingCall;
import static io.grpc.stub.ClientCalls.blockingUnaryCall;
import static io.grpc.stub.ClientCalls.futureUnaryCall;
import static io.grpc.stub.ServerCalls.asyncBidiStreamingCall;
import static io.grpc.stub.ServerCalls.asyncClientStreamingCall;
import static io.grpc.stub.ServerCalls.asyncServerStreamingCall;
import static io.grpc.stub.ServerCalls.asyncUnaryCall;
import static io.grpc.stub.ServerCalls.asyncUnimplementedStreamingCall;
import static io.grpc.stub.ServerCalls.asyncUnimplementedUnaryCall;


public final class BookManagerGrpc {

  private BookManagerGrpc() {}

  public static final String SERVICE_NAME = "library.BookManager";

  // Static method descriptors that strictly reflect the proto.
  private static volatile io.grpc.MethodDescriptor<SincereXIA.distribrpc.book.Request,
      SincereXIA.distribrpc.book.Reply> getAddMethod;

  @io.grpc.stub.annotations.RpcMethod(
      fullMethodName = SERVICE_NAME + '/' + "add",
      requestType = SincereXIA.distribrpc.book.Request.class,
      responseType = SincereXIA.distribrpc.book.Reply.class,
      methodType = io.grpc.MethodDescriptor.MethodType.UNARY)
  public static io.grpc.MethodDescriptor<SincereXIA.distribrpc.book.Request,
      SincereXIA.distribrpc.book.Reply> getAddMethod() {
    io.grpc.MethodDescriptor<SincereXIA.distribrpc.book.Request, SincereXIA.distribrpc.book.Reply> getAddMethod;
    if ((getAddMethod = BookManagerGrpc.getAddMethod) == null) {
      synchronized (BookManagerGrpc.class) {
        if ((getAddMethod = BookManagerGrpc.getAddMethod) == null) {
          BookManagerGrpc.getAddMethod = getAddMethod = 
              io.grpc.MethodDescriptor.<SincereXIA.distribrpc.book.Request, SincereXIA.distribrpc.book.Reply>newBuilder()
              .setType(io.grpc.MethodDescriptor.MethodType.UNARY)
              .setFullMethodName(generateFullMethodName(
                  "library.BookManager", "add"))
              .setSampledToLocalTracing(true)
              .setRequestMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
                  SincereXIA.distribrpc.book.Request.getDefaultInstance()))
              .setResponseMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
                  SincereXIA.distribrpc.book.Reply.getDefaultInstance()))
                  .setSchemaDescriptor(new BookManagerMethodDescriptorSupplier("add"))
                  .build();
          }
        }
     }
     return getAddMethod;
  }

  private static volatile io.grpc.MethodDescriptor<SincereXIA.distribrpc.book.Request,
      SincereXIA.distribrpc.book.Book> getQueryByIDMethod;

  @io.grpc.stub.annotations.RpcMethod(
      fullMethodName = SERVICE_NAME + '/' + "queryByID",
      requestType = SincereXIA.distribrpc.book.Request.class,
      responseType = SincereXIA.distribrpc.book.Book.class,
      methodType = io.grpc.MethodDescriptor.MethodType.UNARY)
  public static io.grpc.MethodDescriptor<SincereXIA.distribrpc.book.Request,
      SincereXIA.distribrpc.book.Book> getQueryByIDMethod() {
    io.grpc.MethodDescriptor<SincereXIA.distribrpc.book.Request, SincereXIA.distribrpc.book.Book> getQueryByIDMethod;
    if ((getQueryByIDMethod = BookManagerGrpc.getQueryByIDMethod) == null) {
      synchronized (BookManagerGrpc.class) {
        if ((getQueryByIDMethod = BookManagerGrpc.getQueryByIDMethod) == null) {
          BookManagerGrpc.getQueryByIDMethod = getQueryByIDMethod = 
              io.grpc.MethodDescriptor.<SincereXIA.distribrpc.book.Request, SincereXIA.distribrpc.book.Book>newBuilder()
              .setType(io.grpc.MethodDescriptor.MethodType.UNARY)
              .setFullMethodName(generateFullMethodName(
                  "library.BookManager", "queryByID"))
              .setSampledToLocalTracing(true)
              .setRequestMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
                  SincereXIA.distribrpc.book.Request.getDefaultInstance()))
              .setResponseMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
                  SincereXIA.distribrpc.book.Book.getDefaultInstance()))
                  .setSchemaDescriptor(new BookManagerMethodDescriptorSupplier("queryByID"))
                  .build();
          }
        }
     }
     return getQueryByIDMethod;
  }

  private static volatile io.grpc.MethodDescriptor<SincereXIA.distribrpc.book.Request,
      SincereXIA.distribrpc.book.BookList> getQueryByNameMethod;

  @io.grpc.stub.annotations.RpcMethod(
      fullMethodName = SERVICE_NAME + '/' + "queryByName",
      requestType = SincereXIA.distribrpc.book.Request.class,
      responseType = SincereXIA.distribrpc.book.BookList.class,
      methodType = io.grpc.MethodDescriptor.MethodType.UNARY)
  public static io.grpc.MethodDescriptor<SincereXIA.distribrpc.book.Request,
      SincereXIA.distribrpc.book.BookList> getQueryByNameMethod() {
    io.grpc.MethodDescriptor<SincereXIA.distribrpc.book.Request, SincereXIA.distribrpc.book.BookList> getQueryByNameMethod;
    if ((getQueryByNameMethod = BookManagerGrpc.getQueryByNameMethod) == null) {
      synchronized (BookManagerGrpc.class) {
        if ((getQueryByNameMethod = BookManagerGrpc.getQueryByNameMethod) == null) {
          BookManagerGrpc.getQueryByNameMethod = getQueryByNameMethod = 
              io.grpc.MethodDescriptor.<SincereXIA.distribrpc.book.Request, SincereXIA.distribrpc.book.BookList>newBuilder()
              .setType(io.grpc.MethodDescriptor.MethodType.UNARY)
              .setFullMethodName(generateFullMethodName(
                  "library.BookManager", "queryByName"))
              .setSampledToLocalTracing(true)
              .setRequestMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
                  SincereXIA.distribrpc.book.Request.getDefaultInstance()))
              .setResponseMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
                  SincereXIA.distribrpc.book.BookList.getDefaultInstance()))
                  .setSchemaDescriptor(new BookManagerMethodDescriptorSupplier("queryByName"))
                  .build();
          }
        }
     }
     return getQueryByNameMethod;
  }

  private static volatile io.grpc.MethodDescriptor<SincereXIA.distribrpc.book.Request,
      SincereXIA.distribrpc.book.Reply> getDeleteMethod;

  @io.grpc.stub.annotations.RpcMethod(
      fullMethodName = SERVICE_NAME + '/' + "delete",
      requestType = SincereXIA.distribrpc.book.Request.class,
      responseType = SincereXIA.distribrpc.book.Reply.class,
      methodType = io.grpc.MethodDescriptor.MethodType.UNARY)
  public static io.grpc.MethodDescriptor<SincereXIA.distribrpc.book.Request,
      SincereXIA.distribrpc.book.Reply> getDeleteMethod() {
    io.grpc.MethodDescriptor<SincereXIA.distribrpc.book.Request, SincereXIA.distribrpc.book.Reply> getDeleteMethod;
    if ((getDeleteMethod = BookManagerGrpc.getDeleteMethod) == null) {
      synchronized (BookManagerGrpc.class) {
        if ((getDeleteMethod = BookManagerGrpc.getDeleteMethod) == null) {
          BookManagerGrpc.getDeleteMethod = getDeleteMethod = 
              io.grpc.MethodDescriptor.<SincereXIA.distribrpc.book.Request, SincereXIA.distribrpc.book.Reply>newBuilder()
              .setType(io.grpc.MethodDescriptor.MethodType.UNARY)
              .setFullMethodName(generateFullMethodName(
                  "library.BookManager", "delete"))
              .setSampledToLocalTracing(true)
              .setRequestMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
                  SincereXIA.distribrpc.book.Request.getDefaultInstance()))
              .setResponseMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
                  SincereXIA.distribrpc.book.Reply.getDefaultInstance()))
                  .setSchemaDescriptor(new BookManagerMethodDescriptorSupplier("delete"))
                  .build();
          }
        }
     }
     return getDeleteMethod;
  }

  private static volatile io.grpc.MethodDescriptor<SincereXIA.distribrpc.book.UserID,
      SincereXIA.distribrpc.book.Reply> getLoginMethod;

  @io.grpc.stub.annotations.RpcMethod(
      fullMethodName = SERVICE_NAME + '/' + "login",
      requestType = SincereXIA.distribrpc.book.UserID.class,
      responseType = SincereXIA.distribrpc.book.Reply.class,
      methodType = io.grpc.MethodDescriptor.MethodType.UNARY)
  public static io.grpc.MethodDescriptor<SincereXIA.distribrpc.book.UserID,
      SincereXIA.distribrpc.book.Reply> getLoginMethod() {
    io.grpc.MethodDescriptor<SincereXIA.distribrpc.book.UserID, SincereXIA.distribrpc.book.Reply> getLoginMethod;
    if ((getLoginMethod = BookManagerGrpc.getLoginMethod) == null) {
      synchronized (BookManagerGrpc.class) {
        if ((getLoginMethod = BookManagerGrpc.getLoginMethod) == null) {
          BookManagerGrpc.getLoginMethod = getLoginMethod = 
              io.grpc.MethodDescriptor.<SincereXIA.distribrpc.book.UserID, SincereXIA.distribrpc.book.Reply>newBuilder()
              .setType(io.grpc.MethodDescriptor.MethodType.UNARY)
              .setFullMethodName(generateFullMethodName(
                  "library.BookManager", "login"))
              .setSampledToLocalTracing(true)
              .setRequestMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
                  SincereXIA.distribrpc.book.UserID.getDefaultInstance()))
              .setResponseMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
                  SincereXIA.distribrpc.book.Reply.getDefaultInstance()))
                  .setSchemaDescriptor(new BookManagerMethodDescriptorSupplier("login"))
                  .build();
          }
        }
     }
     return getLoginMethod;
  }

  /**
   * Creates a new async stub that supports all call types for the service
   */
  public static BookManagerStub newStub(io.grpc.Channel channel) {
    return new BookManagerStub(channel);
  }

  /**
   * Creates a new blocking-style stub that supports unary and streaming output calls on the service
   */
  public static BookManagerBlockingStub newBlockingStub(
      io.grpc.Channel channel) {
    return new BookManagerBlockingStub(channel);
  }

  /**
   * Creates a new ListenableFuture-style stub that supports unary calls on the service
   */
  public static BookManagerFutureStub newFutureStub(
      io.grpc.Channel channel) {
    return new BookManagerFutureStub(channel);
  }

  /**
   */
  public static abstract class BookManagerImplBase implements io.grpc.BindableService {

    /**
     */
    public void add(SincereXIA.distribrpc.book.Request request,
        io.grpc.stub.StreamObserver<SincereXIA.distribrpc.book.Reply> responseObserver) {
      asyncUnimplementedUnaryCall(getAddMethod(), responseObserver);
    }

    /**
     */
    public void queryByID(SincereXIA.distribrpc.book.Request request,
        io.grpc.stub.StreamObserver<SincereXIA.distribrpc.book.Book> responseObserver) {
      asyncUnimplementedUnaryCall(getQueryByIDMethod(), responseObserver);
    }

    /**
     */
    public void queryByName(SincereXIA.distribrpc.book.Request request,
        io.grpc.stub.StreamObserver<SincereXIA.distribrpc.book.BookList> responseObserver) {
      asyncUnimplementedUnaryCall(getQueryByNameMethod(), responseObserver);
    }

    /**
     */
    public void delete(SincereXIA.distribrpc.book.Request request,
        io.grpc.stub.StreamObserver<SincereXIA.distribrpc.book.Reply> responseObserver) {
      asyncUnimplementedUnaryCall(getDeleteMethod(), responseObserver);
    }

    /**
     */
    public void login(SincereXIA.distribrpc.book.UserID request,
        io.grpc.stub.StreamObserver<SincereXIA.distribrpc.book.Reply> responseObserver) {
      asyncUnimplementedUnaryCall(getLoginMethod(), responseObserver);
    }

    @Override public final io.grpc.ServerServiceDefinition bindService() {
      return io.grpc.ServerServiceDefinition.builder(getServiceDescriptor())
          .addMethod(
            getAddMethod(),
            asyncUnaryCall(
              new MethodHandlers<
                SincereXIA.distribrpc.book.Request,
                SincereXIA.distribrpc.book.Reply>(
                  this, METHODID_ADD)))
          .addMethod(
            getQueryByIDMethod(),
            asyncUnaryCall(
              new MethodHandlers<
                SincereXIA.distribrpc.book.Request,
                SincereXIA.distribrpc.book.Book>(
                  this, METHODID_QUERY_BY_ID)))
          .addMethod(
            getQueryByNameMethod(),
            asyncUnaryCall(
              new MethodHandlers<
                SincereXIA.distribrpc.book.Request,
                SincereXIA.distribrpc.book.BookList>(
                  this, METHODID_QUERY_BY_NAME)))
          .addMethod(
            getDeleteMethod(),
            asyncUnaryCall(
              new MethodHandlers<
                SincereXIA.distribrpc.book.Request,
                SincereXIA.distribrpc.book.Reply>(
                  this, METHODID_DELETE)))
          .addMethod(
            getLoginMethod(),
            asyncUnaryCall(
              new MethodHandlers<
                SincereXIA.distribrpc.book.UserID,
                SincereXIA.distribrpc.book.Reply>(
                  this, METHODID_LOGIN)))
          .build();
    }
  }

  /**
   */
  public static final class BookManagerStub extends io.grpc.stub.AbstractStub<BookManagerStub> {
    private BookManagerStub(io.grpc.Channel channel) {
      super(channel);
    }

    private BookManagerStub(io.grpc.Channel channel,
        io.grpc.CallOptions callOptions) {
      super(channel, callOptions);
    }

    @Override
    protected BookManagerStub build(io.grpc.Channel channel,
        io.grpc.CallOptions callOptions) {
      return new BookManagerStub(channel, callOptions);
    }

    /**
     */
    public void add(SincereXIA.distribrpc.book.Request request,
        io.grpc.stub.StreamObserver<SincereXIA.distribrpc.book.Reply> responseObserver) {
      asyncUnaryCall(
          getChannel().newCall(getAddMethod(), getCallOptions()), request, responseObserver);
    }

    /**
     */
    public void queryByID(SincereXIA.distribrpc.book.Request request,
        io.grpc.stub.StreamObserver<SincereXIA.distribrpc.book.Book> responseObserver) {
      asyncUnaryCall(
          getChannel().newCall(getQueryByIDMethod(), getCallOptions()), request, responseObserver);
    }

    /**
     */
    public void queryByName(SincereXIA.distribrpc.book.Request request,
        io.grpc.stub.StreamObserver<SincereXIA.distribrpc.book.BookList> responseObserver) {
      asyncUnaryCall(
          getChannel().newCall(getQueryByNameMethod(), getCallOptions()), request, responseObserver);
    }

    /**
     */
    public void delete(SincereXIA.distribrpc.book.Request request,
        io.grpc.stub.StreamObserver<SincereXIA.distribrpc.book.Reply> responseObserver) {
      asyncUnaryCall(
          getChannel().newCall(getDeleteMethod(), getCallOptions()), request, responseObserver);
    }

    /**
     */
    public void login(SincereXIA.distribrpc.book.UserID request,
        io.grpc.stub.StreamObserver<SincereXIA.distribrpc.book.Reply> responseObserver) {
      asyncUnaryCall(
          getChannel().newCall(getLoginMethod(), getCallOptions()), request, responseObserver);
    }
  }

  /**
   */
  public static final class BookManagerBlockingStub extends io.grpc.stub.AbstractStub<BookManagerBlockingStub> {
    private BookManagerBlockingStub(io.grpc.Channel channel) {
      super(channel);
    }

    private BookManagerBlockingStub(io.grpc.Channel channel,
        io.grpc.CallOptions callOptions) {
      super(channel, callOptions);
    }

    @Override
    protected BookManagerBlockingStub build(io.grpc.Channel channel,
        io.grpc.CallOptions callOptions) {
      return new BookManagerBlockingStub(channel, callOptions);
    }

    /**
     */
    public SincereXIA.distribrpc.book.Reply add(SincereXIA.distribrpc.book.Request request) {
      return blockingUnaryCall(
          getChannel(), getAddMethod(), getCallOptions(), request);
    }

    /**
     */
    public SincereXIA.distribrpc.book.Book queryByID(SincereXIA.distribrpc.book.Request request) {
      return blockingUnaryCall(
          getChannel(), getQueryByIDMethod(), getCallOptions(), request);
    }

    /**
     */
    public SincereXIA.distribrpc.book.BookList queryByName(SincereXIA.distribrpc.book.Request request) {
      return blockingUnaryCall(
          getChannel(), getQueryByNameMethod(), getCallOptions(), request);
    }

    /**
     */
    public SincereXIA.distribrpc.book.Reply delete(SincereXIA.distribrpc.book.Request request) {
      return blockingUnaryCall(
          getChannel(), getDeleteMethod(), getCallOptions(), request);
    }

    /**
     */
    public SincereXIA.distribrpc.book.Reply login(SincereXIA.distribrpc.book.UserID request) {
      return blockingUnaryCall(
          getChannel(), getLoginMethod(), getCallOptions(), request);
    }
  }

  /**
   */
  public static final class BookManagerFutureStub extends io.grpc.stub.AbstractStub<BookManagerFutureStub> {
    private BookManagerFutureStub(io.grpc.Channel channel) {
      super(channel);
    }

    private BookManagerFutureStub(io.grpc.Channel channel,
        io.grpc.CallOptions callOptions) {
      super(channel, callOptions);
    }

    @Override
    protected BookManagerFutureStub build(io.grpc.Channel channel,
        io.grpc.CallOptions callOptions) {
      return new BookManagerFutureStub(channel, callOptions);
    }

    /**
     */
    public com.google.common.util.concurrent.ListenableFuture<SincereXIA.distribrpc.book.Reply> add(
        SincereXIA.distribrpc.book.Request request) {
      return futureUnaryCall(
          getChannel().newCall(getAddMethod(), getCallOptions()), request);
    }

    /**
     */
    public com.google.common.util.concurrent.ListenableFuture<SincereXIA.distribrpc.book.Book> queryByID(
        SincereXIA.distribrpc.book.Request request) {
      return futureUnaryCall(
          getChannel().newCall(getQueryByIDMethod(), getCallOptions()), request);
    }

    /**
     */
    public com.google.common.util.concurrent.ListenableFuture<SincereXIA.distribrpc.book.BookList> queryByName(
        SincereXIA.distribrpc.book.Request request) {
      return futureUnaryCall(
          getChannel().newCall(getQueryByNameMethod(), getCallOptions()), request);
    }

    /**
     */
    public com.google.common.util.concurrent.ListenableFuture<SincereXIA.distribrpc.book.Reply> delete(
        SincereXIA.distribrpc.book.Request request) {
      return futureUnaryCall(
          getChannel().newCall(getDeleteMethod(), getCallOptions()), request);
    }

    /**
     */
    public com.google.common.util.concurrent.ListenableFuture<SincereXIA.distribrpc.book.Reply> login(
        SincereXIA.distribrpc.book.UserID request) {
      return futureUnaryCall(
          getChannel().newCall(getLoginMethod(), getCallOptions()), request);
    }
  }

  private static final int METHODID_ADD = 0;
  private static final int METHODID_QUERY_BY_ID = 1;
  private static final int METHODID_QUERY_BY_NAME = 2;
  private static final int METHODID_DELETE = 3;
  private static final int METHODID_LOGIN = 4;

  private static final class MethodHandlers<Req, Resp> implements
      io.grpc.stub.ServerCalls.UnaryMethod<Req, Resp>,
      io.grpc.stub.ServerCalls.ServerStreamingMethod<Req, Resp>,
      io.grpc.stub.ServerCalls.ClientStreamingMethod<Req, Resp>,
      io.grpc.stub.ServerCalls.BidiStreamingMethod<Req, Resp> {
    private final BookManagerImplBase serviceImpl;
    private final int methodId;

    MethodHandlers(BookManagerImplBase serviceImpl, int methodId) {
      this.serviceImpl = serviceImpl;
      this.methodId = methodId;
    }

    @Override
    @SuppressWarnings("unchecked")
    public void invoke(Req request, io.grpc.stub.StreamObserver<Resp> responseObserver) {
      switch (methodId) {
        case METHODID_ADD:
          serviceImpl.add((SincereXIA.distribrpc.book.Request) request,
              (io.grpc.stub.StreamObserver<SincereXIA.distribrpc.book.Reply>) responseObserver);
          break;
        case METHODID_QUERY_BY_ID:
          serviceImpl.queryByID((SincereXIA.distribrpc.book.Request) request,
              (io.grpc.stub.StreamObserver<SincereXIA.distribrpc.book.Book>) responseObserver);
          break;
        case METHODID_QUERY_BY_NAME:
          serviceImpl.queryByName((SincereXIA.distribrpc.book.Request) request,
              (io.grpc.stub.StreamObserver<SincereXIA.distribrpc.book.BookList>) responseObserver);
          break;
        case METHODID_DELETE:
          serviceImpl.delete((SincereXIA.distribrpc.book.Request) request,
              (io.grpc.stub.StreamObserver<SincereXIA.distribrpc.book.Reply>) responseObserver);
          break;
        case METHODID_LOGIN:
          serviceImpl.login((SincereXIA.distribrpc.book.UserID) request,
              (io.grpc.stub.StreamObserver<SincereXIA.distribrpc.book.Reply>) responseObserver);
          break;
        default:
          throw new AssertionError();
      }
    }

    @Override
    @SuppressWarnings("unchecked")
    public io.grpc.stub.StreamObserver<Req> invoke(
        io.grpc.stub.StreamObserver<Resp> responseObserver) {
      switch (methodId) {
        default:
          throw new AssertionError();
      }
    }
  }

  private static abstract class BookManagerBaseDescriptorSupplier
      implements io.grpc.protobuf.ProtoFileDescriptorSupplier, io.grpc.protobuf.ProtoServiceDescriptorSupplier {
    BookManagerBaseDescriptorSupplier() {}

    @Override
    public com.google.protobuf.Descriptors.FileDescriptor getFileDescriptor() {
      return SincereXIA.distribrpc.book.BookProto.getDescriptor();
    }

    @Override
    public com.google.protobuf.Descriptors.ServiceDescriptor getServiceDescriptor() {
      return getFileDescriptor().findServiceByName("BookManager");
    }
  }

  private static final class BookManagerFileDescriptorSupplier
      extends BookManagerBaseDescriptorSupplier {
    BookManagerFileDescriptorSupplier() {}
  }

  private static final class BookManagerMethodDescriptorSupplier
      extends BookManagerBaseDescriptorSupplier
      implements io.grpc.protobuf.ProtoMethodDescriptorSupplier {
    private final String methodName;

    BookManagerMethodDescriptorSupplier(String methodName) {
      this.methodName = methodName;
    }

    @Override
    public com.google.protobuf.Descriptors.MethodDescriptor getMethodDescriptor() {
      return getServiceDescriptor().findMethodByName(methodName);
    }
  }

  private static volatile io.grpc.ServiceDescriptor serviceDescriptor;

  public static io.grpc.ServiceDescriptor getServiceDescriptor() {
    io.grpc.ServiceDescriptor result = serviceDescriptor;
    if (result == null) {
      synchronized (BookManagerGrpc.class) {
        result = serviceDescriptor;
        if (result == null) {
          serviceDescriptor = result = io.grpc.ServiceDescriptor.newBuilder(SERVICE_NAME)
              .setSchemaDescriptor(new BookManagerFileDescriptorSupplier())
              .addMethod(getAddMethod())
              .addMethod(getQueryByIDMethod())
              .addMethod(getQueryByNameMethod())
              .addMethod(getDeleteMethod())
              .addMethod(getLoginMethod())
              .build();
        }
      }
    }
    return result;
  }
}
