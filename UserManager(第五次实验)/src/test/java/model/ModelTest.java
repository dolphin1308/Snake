package model;

import static org.junit.Assert.*;

import java.util.ArrayList;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import entity.User;

/**
 * Model类的单元测试
 */
public class ModelTest {
    
    private Model model;
    private int testId = 9999; // 使用一个特殊ID进行测试
    private String testName = "测试用户";
    private String testPassword = "test123";
    
    /**
     * 在每个测试方法执行前执行的设置
     */
    @Before
    public void setUp() throws Exception {
        model = new Model();
        // 确保测试前删除可能存在的测试数据
        model.delete(testId);
    }
    
    /**
     * 在每个测试方法执行后执行的清理
     */
    @After
    public void tearDown() throws Exception {
        // 清理测试数据
        model.delete(testId);
    }
    
    /**
     * 测试插入方法
     */
    @Test
    public void testInsert() {
        // 测试插入用户
        int result = model.insert(testId, testName, testPassword);
        assertEquals("插入方法应返回1表示成功", 1, result);
        
        // 验证用户已被插入
        User user = model.load(testId);
        assertNotNull("插入后应能查询到用户", user);
        assertEquals("插入的用户ID应匹配", testId, user.getId());
        assertEquals("插入的用户名应匹配", testName, user.getName());
        assertEquals("插入的密码应匹配", testPassword, user.getPassword());
    }
    
    /**
     * 测试更新方法
     */
    @Test
    public void testUpdate() {
        // 首先插入测试数据
        model.insert(testId, testName, testPassword);
        
        // 更新数据
        String newName = "更新名称";
        String newPassword = "newpass123";
        int result = model.update(testId, newName, newPassword);
        assertEquals("更新方法应返回1表示成功", 1, result);
        
        // 验证数据已更新
        User updatedUser = model.load(testId);
        assertNotNull("更新后应能查询到用户", updatedUser);
        assertEquals("更新后用户ID应保持不变", testId, updatedUser.getId());
        assertEquals("用户名应已更新", newName, updatedUser.getName());
        assertEquals("密码应已更新", newPassword, updatedUser.getPassword());
    }
    
    /**
     * 测试删除方法
     */
    @Test
    public void testDelete() {
        // 首先插入测试数据
        model.insert(testId, testName, testPassword);
        
        // 删除数据
        int result = model.delete(testId);
        assertEquals("删除方法应返回1表示成功", 1, result);
        
        // 验证数据已被删除（load方法在找不到用户时会返回一个新的User对象，但其字段为默认值）
        User deletedUser = model.load(testId);
        assertEquals("删除后用户ID应为0", 0, deletedUser.getId());
        assertNull("删除后用户名应为null", deletedUser.getName());
        assertNull("删除后密码应为null", deletedUser.getPassword());
    }
    
    /**
     * 测试通过ID加载用户
     */
    @Test
    public void testLoad() {
        // 首先插入测试数据
        model.insert(testId, testName, testPassword);
        
        // 测试加载方法
        User loadedUser = model.load(testId);
        assertNotNull("应能加载到插入的用户", loadedUser);
        assertEquals("加载的用户ID应匹配", testId, loadedUser.getId());
        assertEquals("加载的用户名应匹配", testName, loadedUser.getName());
        assertEquals("加载的密码应匹配", testPassword, loadedUser.getPassword());
        
        // 测试加载不存在的用户
        model.delete(testId);
        User nonExistUser = model.load(testId);
        assertEquals("不存在的用户ID应为0", 0, nonExistUser.getId());
    }
    
    /**
     * 测试查询所有用户
     */
    @Test
    public void testUserSelect() {
        // 首先插入测试数据
        model.insert(testId, testName, testPassword);
        
        // 测试查询所有用户
        ArrayList<User> users = model.userSelect();
        assertNotNull("用户列表不应为null", users);
        assertFalse("用户列表不应为空", users.isEmpty());
        
        // 检查是否包含测试用户
        boolean foundTestUser = false;
        for (User user : users) {
            if (user.getId() == testId) {
                foundTestUser = true;
                assertEquals("查询到的用户名应匹配", testName, user.getName());
                assertEquals("查询到的密码应匹配", testPassword, user.getPassword());
                break;
            }
        }
        assertTrue("用户列表应包含测试用户", foundTestUser);
    }
} 