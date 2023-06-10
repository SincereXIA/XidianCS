package xdu.jzh;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.jdbc.DataSourceAutoConfiguration;
import org.springframework.cloud.openfeign.EnableFeignClients;

/**
 * @author akyna
 * @date 05/30 030 8:22 PM
 */
@SpringBootApplication(exclude =  {DataSourceAutoConfiguration.class })
@EnableFeignClients
public class ConsumerMain {
    public static void main(String[] args) {
        SpringApplication.run(ConsumerMain.class, args);
    }
}
