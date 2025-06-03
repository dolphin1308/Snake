<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <title>删除用户</title>
    <link rel="stylesheet" type="text/css" href="css/common.css">
  </head>
  <body>
    <h1>删除用户</h1>
    <div class="container">
      <form action="deleShow.jsp" method="post">
        <div class="form-group">
          <label for="id">请输入要删除的用户ID：</label>
          <input type="text" id="id" name="id">
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
