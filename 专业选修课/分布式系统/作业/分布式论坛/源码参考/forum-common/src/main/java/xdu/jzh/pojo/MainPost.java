package xdu.jzh.pojo;

import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.ToString;

/**
 * @author akyna
 * @date 05/30 030 4:43 PM
 */
@Data
@ToString
@NoArgsConstructor
@AllArgsConstructor
@TableName("t_main_post")
public class MainPost {
    @TableId
    private String id;
    private String msg;
    private Long vts;
}
