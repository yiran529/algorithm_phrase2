采用Ford-Fulkerson算法解决最大流问题，理解要点：
1.这个算法的正确性：不再存在增强路径←→找到了最大流
2.找到了最大流，也就找到了最小切割：
	value of the maxflow=capacity of mincut
  求解得到最大流后，怎么得到最小切割的具体位置：
	假设最小切割将图形分为A与B两个部分，找到A=set of
	vertices connected to s by an undirected path with
	no full forward or empty backward edges.
	（这部分我没有实现）
3.具体实现时找增强路径的方法：残差网络与BFS
   其它一些具体实现时的细节……
没有理解的问题：
1.FF算法正确性的证明有部分不理解
2.最大流问题的应用	