package xdu.jzh.service;

import org.springframework.cloud.openfeign.FeignClient;
import org.springframework.stereotype.Service;
import org.springframework.web.bind.annotation.*;
import xdu.jzh.pojo.MainPost;
import xdu.jzh.pojo.ReplyPost;

import java.util.List;

/**
 * @author akyna
 * @date 05/31 031 4:08 PM
 */
@Service
@FeignClient("FORUM-SERVICE")
public interface ForumService {
    // 新增主贴
    @PostMapping("/posts/main")
    MainPost createPost(@RequestBody MainPost mainPost);

    // 回复主贴
    @PostMapping("/posts/reply")
    ReplyPost replyPost(@RequestBody ReplyPost replyPost);

    // 根据主贴 id 获取主贴
    @GetMapping("/posts/{id}")
    MainPost getMainPost(@PathVariable String id);

    // 根据主贴 id 获取回帖
    @GetMapping("/posts/{id}/replies")
    List<ReplyPost> getReplies(@PathVariable String id);
}
