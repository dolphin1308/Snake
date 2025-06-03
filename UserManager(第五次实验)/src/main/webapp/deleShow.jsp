<%@ page language="java" import="java.util.*,dbutil.*,entity.*,model.*" pageEncoding="UTF-8"%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <title>删除结果</title>
    <link rel="stylesheet" type="text/css" href="css/common.css">
  </head>
  <body>
    <h1>删除用户结果</h1>
    <div class="container">
      <%
        request.setCharacterEncoding("UTF-8");
        int id=Integer.parseInt(request.getParameter("id"));
        Model model=new Model();
        int i=model.delete(id);
        if(i==1){
          %>
          <div class="form-group">
            <p>删除用户成功！</p>
          </div>
          <%
        }else{
          %>
          <div class="form-group">
            <p>删除用户失败！</p>
          </div>
          <%
        }
      %>
      
      <div class="home-link">
        <a href="index.jsp" class="btn">返回首页</a>
        <a href="dele.jsp" class="btn">继续删除</a>
      </div>
    </div>
  </body>
</html>
