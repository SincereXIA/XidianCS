package xdu.jzh;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.netflix.eureka.server.EnableEurekaServer;

/**
 * @author akyna
 * @date 05/30 030 4:34 PM
 */
@SpringBootApplication
@EnableEurekaServer
public class ForumCenterMain {
    public static void main(String[] args) {
        SpringApplication.run(ForumCenterMain.class, args);
    }
}
