import edu.princeton.cs.algs4.*;


public class Percolation {
    private UF uf;
    private int N;
    private boolean isopen[][];
    private boolean isfulled[][];
    boolean isVisited[][];
    public Painter painter;

    private int getUFId(int x, int y){
        return (y*N + x + 1);
    }

    /**
     * 初始化大小为 N 的可渗透区域
     * @param N 渗透区域大小
     */
    public Percolation(int N){
        this.N = N;
        uf = new UF(N*N+2);
        /* 设水源位于 0，将第一行与水源相连*
         */
        for (int i = 0; i< N;i++){
            uf.union(0, getUFId(i,0));
        }
        for (int i = 0; i< N;i++){
            uf.union(N*N+1, getUFId(i,N-1));
        }

        isopen = new boolean[N][N];

        for (int i = 0;i <N;i++){
            for (int j = 0; j<N;j++){
                isopen[i][j] = false;
            }
        }
        isfulled = new boolean[N][N];
        for (int i = 0;i <N;i++){
            for (int j = 0; j<N;j++){
                isfulled[i][j] = false;
            }
        }
        painter = new Painter(N);
        isVisited = new boolean[N][N];
    }

    /**
     * 开放 x y 处的点
     * @param x 点的横坐标
     * @param y 点的纵坐标
     */
    public void open(int x, int y){
        if (isopen(x, y)) return;
        isopen[x][y] = true;
        painter.printOpen(x,y);
        int dx[] = {0,0,-1,1};
        int dy[] = {1,-1,0,0};
        for (int i = 0; i<4;i++){
            if (isopen(x+dx[i],y+dy[i])){
                uf.union(getUFId(x+dx[i],y+dy[i]), getUFId(x,y));
            }
        }
//        if (isFull(x,y)){
//            for (int i = 0; i<N;i++){
//                for (int j = 0; j<N;j++){
//                    if (isFull(i,j))
//                        painter.printFull(i,j);
//                }
//            }
//        }
        if (isFull(x,y))    bfsIsFull(x,y);
    }

    /**
     * 判断 x y 处的点是否开放
     * @param x 点的横坐标
     * @param y 点的纵坐标
     */
    public boolean isopen(int x, int y){
        if (x<0 || x>=N || y<0 || y>=N){
            return false;
        }else {
            return isopen[x][y];
        }
    }

    /**
     * 判断 x y 点处是否已经注入水（绘图用）
     * @param x 点的横坐标
     * @param y 点的纵坐标
     */
    public boolean isFull(int x, int y){
        return isopen(x, y) && uf.connected(0, getUFId(x, y));
    }

    /**
     * 判断全图是否渗透
     *
     * @return true 渗透
     */
    public boolean percolates(){
        return uf.connected(0,N*N+1);
    }

    public int openSize(){
        int num = 0;
        for(int i = 0;i<N;i++){
            for (int j = 0; j<N;j++){
                if(isopen(i,j)){
                    num++;
                }
            }
        }
        return num;
    }

    private void bfsIsFull(int x, int y){
        if (!isFull(x,y))   return;
        for (int i = 0; i<N;i++){
            for (int j = 0; j<N;j++){
                isVisited[i][j] = false;
            }
        }

        Queue<Node> queue = new Queue<>();
        queue.enqueue(new Node(x,y));
        while (!queue.isEmpty()){
            Node n = queue.dequeue();
            painter.printFull(n.x,n.y);
            isfulled[n.x][n.y] = true;
            int dx[] = {0,0,-1,1};
            int dy[] = {1,-1,0,0};
            for (int i = 0; i<4;i++){
                int nx = n.x +dx[i];
                int ny = n.y +dy[i];
                if (isopen(nx,ny) && ! isVisited[nx][ny] && (!isfulled[nx][ny])){
                    isVisited[nx][ny] = true;
                    queue.enqueue(new Node(nx,ny));
                }
            }
        }
    }

    private class Node{
        int x, y;
        public Node(int x, int y){
            this.x = x;
            this.y = y;
        }
    }
}

