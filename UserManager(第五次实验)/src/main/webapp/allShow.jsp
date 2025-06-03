<%@ page language="java" import="java.util.*,dbutil.*,entity.*,model.*" pageEncoding="utf-8"%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <title>显示数据页面</title>
    <link rel="stylesheet" type="text/css" href="css/common.css">
  </head>
  <body>
    <h1>数据库中所有用户</h1>
    <div class="container">
      <%
       Model model=new Model();
       ArrayList<User> arraylist=model.userSelect();
      %>
      <table>
        <tr>
          <th>ID</th>
          <th>用户名</th>
          <th>密码</th>
        </tr>
        <%for(int i=0;i<arraylist.size();i++){%>
          <tr>
            <td><%=arraylist.get(i).getId()%></td>
            <td><%=arraylist.get(i).getName() %></td>
            <td><%=arraylist.get(i).getPassword() %></td>
          </tr>
        <% } %>
      </table>
      
      <div class="home-link">
        <a href="index.jsp" class="btn">返回首页</a>
      </div>
    </div>
  </body>
</html>
