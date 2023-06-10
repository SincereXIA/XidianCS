package xdu.jzh.controller;

import cn.hutool.core.util.IdUtil;
import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.web.bind.annotation.*;
import xdu.jzh.pojo.MainPost;
import xdu.jzh.pojo.ReplyPost;
import xdu.jzh.service.MainPostService;
import xdu.jzh.service.ReplyPostService;

import java.util.List;

/**
 * @author akyna
 * @date 05/30 030 5:13 PM
 */
@RestController
@Slf4j
@RequestMapping("/posts")
public class MyPostController {
    private final MainPostService mainPostService;
    private final ReplyPostService replyPostService;

    @Autowired
    public MyPostController(MainPostService mainPostService, ReplyPostService replyPostService) {
        this.mainPostService = mainPostService;
        this.replyPostService = replyPostService;
    }

    @Value("${snowflake.datacenter-id}")
    private Long datacenterId;
    @Value("${snowflake.worker-id}")
    private Long workerId;

    // 新增主贴
    @PostMapping("/main")
    public MainPost createPost(@RequestBody MainPost mainPost) {
        long id = IdUtil.getSnowflake(workerId, datacenterId).nextId();
        mainPost.setId(String.valueOf(id));
        mainPost.setVts(System.currentTimeMillis());
        log.info("create post: {}", mainPost);
        mainPostService.save(mainPost);
        return mainPost;
    }

    // 回复主贴
    @PostMapping("/reply")
    public ReplyPost replyPost(@RequestBody ReplyPost replyPost) {
        long replyId = IdUtil.getSnowflake(workerId, datacenterId).nextId();
        replyPost.setId(String.valueOf(replyId));
        replyPost.setVts(System.currentTimeMillis());
        log.info("reply post: {}", replyPost);
        replyPostService.save(replyPost);
        return replyPost;
    }

    // 根据主贴 id 获取主贴
    @GetMapping("/{id}")
    public MainPost getMainPost(@PathVariable String id) {
        log.info("get main post by id: {}", id);
        return mainPostService.getById(id);
    }

    // 根据主贴 id 获取回帖
    @GetMapping("/{id}/replies")
    public List<ReplyPost> getReplies(@PathVariable String id) {
        QueryWrapper<ReplyPost> wrapper = new QueryWrapper<>();
        wrapper.eq("post_id", id);
        log.info("get replies in main post by id: {} ", id);
        return replyPostService.list(wrapper);
    }
}
