package dbutil;

import static org.junit.Assert.*;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

/**
 * 数据库连接类的单元测试
 */
public class DbconnTest {
    
    private Dbconn dbconn;
    
    /**
     * 在每个测试方法执行前执行的设置
     */
    @Before
    public void setUp() throws Exception {
        dbconn = new Dbconn();
    }
    
    /**
     * 在每个测试方法执行后执行的清理
     */
    @After
    public void tearDown() throws Exception {
    }
    
    /**
     * 测试数据库连接获取方法
     */
    @Test
    public void testGetConnection() {
        try {
            Connection conn = dbconn.getConnection();
            assertNotNull("数据库连接不应为null", conn);
            assertFalse("数据库连接应该是开放的", conn.isClosed());
            conn.close();
        } catch (SQLException e) {
            fail("获取数据库连接时抛出异常: " + e.getMessage());
        }
    }
    
    /**
     * 测试关闭所有资源的方法
     */
    @Test
    public void testCloseAll() {
        Connection conn = null;
        Statement stmt = null;
        ResultSet rs = null;
        
        try {
            conn = dbconn.getConnection();
            stmt = conn.createStatement();
            rs = stmt.executeQuery("SELECT 1");
            
            // 测试关闭所有资源
            dbconn.closeAll(conn, stmt, rs);
            
            assertTrue("连接应已关闭", conn.isClosed());
            assertTrue("语句应已关闭", stmt.isClosed());
            assertTrue("结果集应已关闭", rs.isClosed());
            
        } catch (SQLException e) {
            fail("测试关闭资源时抛出异常: " + e.getMessage());
        }
    }
    
    /**
     * 测试SQL查询是否正常工作
     */
    @Test
    public void testSqlExecution() {
        Connection conn = null;
        Statement stmt = null;
        ResultSet rs = null;
        
        try {
            conn = dbconn.getConnection();
            
            // 执行一个简单的SQL查询
            stmt = conn.createStatement();
            rs = stmt.executeQuery("SELECT 1 as test_value");
            
            assertTrue("查询应返回结果", rs.next());
            assertEquals("查询结果应为1", 1, rs.getInt("test_value"));
            
            dbconn.closeAll(conn, stmt, rs);
            
        } catch (SQLException e) {
            fail("执行SQL查询时抛出异常: " + e.getMessage());
        }
    }
} 