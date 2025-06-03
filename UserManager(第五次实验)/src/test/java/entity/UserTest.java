package entity;

import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

/**
 * User实体类的单元测试
 */
public class UserTest {
    
    private User user;
    private int testId = 1001;
    private String testName = "测试用户";
    private String testPassword = "test123";
    
    /**
     * 在每个测试方法执行前执行的设置
     */
    @Before
    public void setUp() throws Exception {
        user = new User();
    }
    
    /**
     * 在每个测试方法执行后执行的清理
     */
    @After
    public void tearDown() throws Exception {
        user = null;
    }
    
    /**
     * 测试用户ID的getter和setter方法
     */
    @Test
    public void testGetSetId() {
        user.setId(testId);
        assertEquals("用户ID getter/setter应正常工作", testId, user.getId());
    }
    
    /**
     * 测试用户名的getter和setter方法
     */
    @Test
    public void testGetSetName() {
        user.setName(testName);
        assertEquals("用户名 getter/setter应正常工作", testName, user.getName());
    }
    
    /**
     * 测试密码的getter和setter方法
     */
    @Test
    public void testGetSetPassword() {
        user.setPassword(testPassword);
        assertEquals("密码 getter/setter应正常工作", testPassword, user.getPassword());
    }
    
    /**
     * 测试完整的User对象初始化和属性读取
     */
    @Test
    public void testFullUserObject() {
        // 设置所有属性
        user.setId(testId);
        user.setName(testName);
        user.setPassword(testPassword);
        
        // 验证所有属性
        assertEquals("用户ID应匹配", testId, user.getId());
        assertEquals("用户名应匹配", testName, user.getName());
        assertEquals("密码应匹配", testPassword, user.getPassword());
    }
} 