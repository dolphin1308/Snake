<%@ page language="java" import="java.util.*,dbutil.*,entity.*,model.*,java.io.*,org.apache.poi.ss.usermodel.*,org.apache.poi.xssf.usermodel.*,org.apache.poi.hssf.usermodel.*,org.apache.commons.fileupload.*,org.apache.commons.fileupload.disk.*,org.apache.commons.fileupload.servlet.*" pageEncoding="UTF-8"%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
    <title>Excel批量导入结果</title>
    <link rel="stylesheet" type="text/css" href="css/common.css">
</head>
<body>
    <h1>Excel批量导入结果</h1>
    <div class="container">
        <%
            // 创建统计变量
            int successCount = 0;
            int failCount = 0;
            List<String> errors = new ArrayList<>();
            
            // 检查请求是否包含multipart内容
            boolean isMultipart = ServletFileUpload.isMultipartContent(request);
            if (isMultipart) {
                try {
                    // 创建一个基于磁盘的文件项工厂
                    DiskFileItemFactory factory = new DiskFileItemFactory();
                    
                    // 设置临时目录
                    File tmpDir = new File(System.getProperty("java.io.tmpdir"));
                    factory.setRepository(tmpDir);
                    
                    // 创建文件上传处理器
                    ServletFileUpload upload = new ServletFileUpload(factory);
                    
                    // 解析请求，获取文件项
                    List<FileItem> items = upload.parseRequest(request);
                    
                    // 初始化Model
                    Model model = new Model();
                    
                    // 处理上传的文件项
                    for (FileItem item : items) {
                        if (!item.isFormField()) {
                            // 获取上传的文件名
                            String fileName = item.getName();
                            
                            // 检查是否为Excel文件
                            if (fileName.endsWith(".xls") || fileName.endsWith(".xlsx")) {
                                // 创建工作簿
                                Workbook workbook;
                                if (fileName.endsWith(".xlsx")) {
                                    workbook = new XSSFWorkbook(item.getInputStream());
                                } else {
                                    workbook = new HSSFWorkbook(item.getInputStream());
                                }
                                
                                // 获取第一个工作表
                                Sheet sheet = workbook.getSheetAt(0);
                                
                                // 遍历行
                                for (int i = 1; i <= sheet.getLastRowNum(); i++) { // 从第2行开始，跳过标题行
                                    Row row = sheet.getRow(i);
                                    if (row != null) {
                                        try {
                                            // 读取各列数据
                                            int id = (int) row.getCell(0).getNumericCellValue();
                                            String name = row.getCell(1).getStringCellValue();
                                            String password = row.getCell(2).getStringCellValue();
                                            
                                            // 插入用户
                                            int result = model.insert(id, name, password);
                                            if (result == 1) {
                                                successCount++;
                                            } else {
                                                failCount++;
                                                errors.add("第" + (i + 1) + "行：插入失败，可能ID已存在");
                                            }
                                        } catch (Exception e) {
                                            failCount++;
                                            errors.add("第" + (i + 1) + "行：数据格式错误 - " + e.getMessage());
                                        }
                                    }
                                }
                                
                                // 关闭工作簿
                                workbook.close();
                            } else {
                                out.println("<div class='form-group'><p class='error'>上传的文件不是Excel格式！</p></div>");
                            }
                        }
                    }
                } catch (Exception e) {
                    out.println("<div class='form-group'><p class='error'>文件处理错误：" + e.getMessage() + "</p></div>");
                }
            } else {
                out.println("<div class='form-group'><p class='error'>请求不包含文件上传！</p></div>");
            }
        %>
        
        <div class="form-group">
            <h3>导入结果摘要</h3>
            <p>成功导入用户数：<%= successCount %></p>
            <p>失败导入用户数：<%= failCount %></p>
        </div>
        
        <% if (!errors.isEmpty()) { %>
            <div class="form-group">
                <h3>错误详情</h3>
                <ul class="error-list">
                    <% for (String error : errors) { %>
                        <li><%= error %></li>
                    <% } %>
                </ul>
            </div>
        <% } %>
        
        <div class="home-link">
            <a href="index.jsp" class="btn">返回首页</a>
            <a href="insert.jsp" class="btn">继续添加</a>
            <a href="allShow.jsp" class="btn">查看所有用户</a>
        </div>
    </div>
</body>
</html> 