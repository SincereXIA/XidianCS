package xdu.jzh.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import xdu.jzh.pojo.MainPost;
import xdu.jzh.pojo.ReplyPost;
import xdu.jzh.service.ForumService;

import java.util.List;

/**
 * @author akyna
 * @date 05/31 031 4:12 PM
 */
@RestController
@RequestMapping("/posts")
public class ForumController {
    private final ForumService forumService;

    @Autowired
    public ForumController(ForumService forumService) {
        this.forumService = forumService;
    }

    // 新增主贴
    @PostMapping("/main")
    public MainPost createPost(@RequestBody MainPost mainPost) {
        return forumService.createPost(mainPost);
    }

    // 回复主贴
    @PostMapping("/reply")
    public ReplyPost replyPost(@RequestBody ReplyPost replyPost) {
        return forumService.replyPost(replyPost);
    }

    // 根据主贴 id 获取主贴
    @GetMapping("/{id}")
    public MainPost getMainPost(@PathVariable String id) {
        return forumService.getMainPost(id);
    }

    // 根据主贴 id 获取回帖
    @GetMapping("/{id}/replies")
    public List<ReplyPost> getReplies(@PathVariable String id) {
        return forumService.getReplies(id);
    }
}