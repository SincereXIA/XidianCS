package xdu.jzh.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import org.springframework.stereotype.Service;
import xdu.jzh.mapper.MainPostMapper;
import xdu.jzh.pojo.MainPost;
import xdu.jzh.service.MainPostService;

/**
 * @author akyna
 * @date 05/30 030 5:09 PM
 */
@Service
public class MainPostServiceImpl extends ServiceImpl<MainPostMapper, MainPost> implements MainPostService {
}
