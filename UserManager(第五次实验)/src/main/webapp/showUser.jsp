<%@ page language="java" import="java.util.*,dbutil.*,entity.*,model.*" pageEncoding="UTF-8"%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <title>用户信息</title>
    <link rel="stylesheet" type="text/css" href="css/common.css">
  </head>
  <body>
    <h1>用户详细信息</h1>
    <div class="container">
      <%
        int id=Integer.parseInt(request.getParameter("id"));
        Model model=new Model();
        User user=model.load(id);
      %>
      
      <table>
        <tr>
          <th>用户ID</th>
          <th>用户名</th>
          <th>密码</th>
        </tr>
        <tr>
          <td><%=user.getId()%></td>
          <td><%=user.getName()%></td>
          <td><%=user.getPassword()%></td>
        </tr>
      </table>
      
      <div class="home-link">
        <a href="index.jsp" class="btn">返回首页</a>
      </div>
    </div>
  </body>
</html>
