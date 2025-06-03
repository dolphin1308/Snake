import org.junit.runner.RunWith;
import org.junit.runners.Suite;
import org.junit.runners.Suite.SuiteClasses;

import dbutil.DbconnTest;
import entity.UserTest;
import model.ModelTest;

/**
 * 测试套件类，用于运行所有测试类
 */
@RunWith(Suite.class)
@SuiteClasses({
    DbconnTest.class,
    UserTest.class,
    ModelTest.class
})
public class AllTests {
    // 测试套件
} 