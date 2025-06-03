<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <title>添加用户</title>
    <link rel="stylesheet" type="text/css" href="css/common.css">
  </head>
  <body>
    <h1>添加新用户</h1>
    <div class="container">
      <h2>单个用户添加</h2>
      <form action="insertShow.jsp" method="post">
        <div class="form-group">
          <label for="id">用户ID：</label>
          <input type="text" id="id" name="id">
        </div>
        <div class="form-group">
          <label for="name">用户名称：</label>
          <input type="text" id="name" name="name">
        </div>
        <div class="form-group">
          <label for="password">用户密码：</label>
          <input type="text" id="password" name="password">
        </div>
        <div class="form-group">
          <input type="submit" value="提交" class="btn">
        </div>
      </form>
      
      <hr style="margin: 30px 0; border-top: 1px solid #eee;">
      
      <h2>批量导入用户</h2>
      <p>请上传Excel文件（.xls或.xlsx格式），文件需包含ID、用户名和密码三列</p>
      <p><a href="downloadTemplate.jsp" class="btn">下载Excel模板</a></p>
      <form action="excelImport.jsp" method="post" enctype="multipart/form-data">
        <div class="form-group">
          <label for="excelFile">选择Excel文件：</label>
          <input type="file" id="excelFile" name="excelFile" accept=".xls,.xlsx">
        </div>
        <div class="form-group">
          <input type="submit" value="批量导入" class="btn">
        </div>
      </form>
      
      <div class="home-link">
        <a href="index.jsp" class="btn">返回首页</a>
      </div>
    </div>
  </body>
</html>
