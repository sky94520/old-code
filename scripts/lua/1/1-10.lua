--图
--获得图对应的结点 不存在则创建
function name2node(graph,name)
	--不存在该节点
	if not graph[name] then
		graph[name] = {["name"] = name,adj = {}};
	end
	return graph[name];
end
--
