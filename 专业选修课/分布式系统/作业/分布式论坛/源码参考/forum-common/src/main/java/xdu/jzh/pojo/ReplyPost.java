package xdu.jzh.pojo;

import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.ToString;

/**
 * @author akyna
 * @date 05/30 030 4:54 PM
 */
@Data
@ToString
@NoArgsConstructor
@AllArgsConstructor
@TableName("t_reply_post")
public class ReplyPost {
    @TableId
    private String id;
    private String postId;
    private String msg;
    private Long vts;
}
