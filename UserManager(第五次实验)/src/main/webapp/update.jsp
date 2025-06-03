<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <title>修改用户</title>
    <link rel="stylesheet" type="text/css" href="css/common.css">
  </head>
  <body>
    <h1>修改用户信息</h1>
    <div class="container">
      <form action="updateShow.jsp" method="post">
        <div class="form-group">
          <label for="id">用户ID：</label>
          <input type="text" id="id" name="id">
        </div>
        <div class="form-group">
          <label for="name">新用户名：</label>
          <input type="text" id="name" name="name">
        </div>
        <div class="form-group">
          <label for="password">新密码：</label>
          <input type="text" id="password" name="password">
        </div>
        <div class="form-group">
          <input type="submit" value="提交" class="btn">
        </div>
      </form>
      
      <div class="home-link">
        <a href="index.jsp" class="btn">返回首页</a>
      </div>
    </div>
  </body>
</html>