<%@ page language="java" import="java.util.*,java.io.*,org.apache.poi.ss.usermodel.*,org.apache.poi.xssf.usermodel.*" pageEncoding="UTF-8"%>
<%
    // 设置响应内容类型
    response.setContentType("application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
    response.setHeader("Content-Disposition", "attachment; filename=user_import_template.xlsx");

    try {
        // 创建工作簿
        Workbook workbook = new XSSFWorkbook();
        
        // 创建工作表
        Sheet sheet = workbook.createSheet("用户数据");
        
        // 创建标题行样式
        CellStyle headerStyle = workbook.createCellStyle();
        Font font = workbook.createFont();
        font.setBold(true);
        headerStyle.setFont(font);
        headerStyle.setFillForegroundColor(IndexedColors.GREY_25_PERCENT.getIndex());
        headerStyle.setFillPattern(FillPatternType.SOLID_FOREGROUND);
        
        // 创建标题行
        Row headerRow = sheet.createRow(0);
        Cell cell0 = headerRow.createCell(0);
        cell0.setCellValue("用户ID");
        cell0.setCellStyle(headerStyle);
        
        Cell cell1 = headerRow.createCell(1);
        cell1.setCellValue("用户名");
        cell1.setCellStyle(headerStyle);
        
        Cell cell2 = headerRow.createCell(2);
        cell2.setCellValue("密码");
        cell2.setCellStyle(headerStyle);
        
        // 创建示例数据行
        Row dataRow = sheet.createRow(1);
        dataRow.createCell(0).setCellValue(1001);
        dataRow.createCell(1).setCellValue("示例用户");
        dataRow.createCell(2).setCellValue("password123");
        
        // 调整列宽
        sheet.setColumnWidth(0, 3000);
        sheet.setColumnWidth(1, 6000);
        sheet.setColumnWidth(2, 5000);
        
        // 写入响应输出流
        workbook.write(response.getOutputStream());
        workbook.close();
        
    } catch (Exception e) {
        e.printStackTrace();
    }
    
    // 确保不执行后续代码
    out.clear();
    out = pageContext.pushBody();
%> 