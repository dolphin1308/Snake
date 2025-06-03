<%@ page language="java" import="java.util.*,dbutil.*,entity.*,model.*" pageEncoding="UTF-8"%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <title>更新结果</title>
    <link rel="stylesheet" type="text/css" href="css/common.css">
  </head>
  <body>
    <h1>更新用户结果</h1>
    <div class="container">
      <%
        request.setCharacterEncoding("UTF-8");
        int id=Integer.parseInt(request.getParameter("id"));
        String name=request.getParameter("name");
        String password=request.getParameter("password");
        Model model=new Model();
        int i=model.update(id, name, password);
        if(i==1){
          %>
          <div class="form-group">
            <p>更新用户成功！</p>
          </div>
          <%
        }else{
          %>
          <div class="form-group">
            <p>更新用户失败！</p>
          </div>
          <%
        }
      %>
      
      <div class="home-link">
        <a href="index.jsp" class="btn">返回首页</a>
        <a href="update.jsp" class="btn">继续更新</a>
      </div>
    </div>
  </body>
</html>