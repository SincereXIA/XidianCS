package xdu.jzh;

import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

/**
 * @author akyna
 * @date 05/30 030 4:38 PM
 */
@SpringBootApplication
@MapperScan("xdu.jzh.mapper")
public class ForumService8002 {
    public static void main(String[] args) {
        SpringApplication.run(ForumService8002.class, args);
    }
}
