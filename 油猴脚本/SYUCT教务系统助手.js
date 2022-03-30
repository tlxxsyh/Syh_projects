// ==UserScript==
// @name         SYUCT沈阳化工大学教务系统助手
// @namespace    http://tampermonkey.net/
// @version      2.1
// @description  教务系统自动填写账号密码，按下回车一键自动评教，iframe框架内显示看板娘功能
// @author       Yuhang Shang
// @match        *://jws.syuct.edu.cn/*
// @icon         https://www.shangyuhang.icu/favicon/64_64.ico
// @grant        none
// @license      MIT
// ==/UserScript==
 
(function() {
    'use strict';
    
    //抢课卡进服务器专用
    document.querySelector("#content_no > p:nth-child(5) > a").click();
    //使用帮助
    //在使用脚本按键前：请先点击评教页面表格任意位置，使脚本能够获取焦点
    //按下回车键自动填写教师评价（随机一行是良好，其余行均为优秀）
 
    //=======================================
    //    请在此填写您的账号和密码
    //=======================================
    var your_username='你的学号';
    var your_password='你的密码';
 
    //全局变量
    var StudentLoginURL='default2.aspx';//学生登录页面url
    var iiframe;//用来获取内部iframe框架的变量
    var girl_link;//存储引入桌宠项目所需添加的link元素
    var girl_script;//存储引入桌宠项目所需添加的script元素
    var randNum;//随机数
 
    //键盘监听事件
    document.addEventListener('keydown', my);
    function my(e){
        if(e.keyCode==13){
            //window.alert("press")
            write();
        }
    }
 
    //自动评价功能
    function write(){
        //先将所有行全填为优秀
        let rows=document.querySelector('#DataGrid1').rows.length-1;
        for(let i=0;i<rows;i++){
            let my_selector='#DataGrid1__ctl'+(i+2)+'_JS1';
            document.querySelector(my_selector).value='优秀';
            //console.log(my_selector);
        }
        //再随机一行填为良好
        randNum=randomNum(2,1+rows);
        let my_selector2='#DataGrid1__ctl'+randNum+'_JS1';
        document.querySelector(my_selector2).value='良好';
        //var final=document.getElementById('DataGrid1__ctl2_JS1');
        //final.value='良好';
        document.querySelector('#Button1').click();
    }
 
    //随机函数，返回一个介于minNum和maxNum之间的值（包括两端边界）
     function randomNum(minNum,maxNum){
        switch(arguments.length){
            case 1:
                return parseInt(Math.random()*minNum+1,10);break;
            case 2:
                return parseInt(Math.random()*(maxNum-minNum+1)+minNum,10);break;
            default:
                return 0;break;
        }
    }
 
    //学生登录系统
    var windowURL = window.location.href;
    if (windowURL.indexOf(StudentLoginURL) != -1) {
        createGirl();
        document.querySelector('#txtUserName').value=your_username;
        document.querySelector('#TextBox2').value=your_password;
    }
 
    //添加看板娘
    //createGirl();
    //window.onload=function {setTimeout(deleteGirl(),5000);}
 
    //判断是否有iframe框架
    if(iiframe = document.getElementById('iframeautoheight'))
    {
        //等待内部框架加载完毕再生成看板娘
        iiframe.onload=function(){
            //获取iframe窗口句柄
            iiframe = document.getElementById('iframeautoheight').contentWindow;
            //添加link元素
            girl_link = iiframe.document.createElement('link');
            girl_link.setAttribute('hreflang','zh');
            girl_link.setAttribute('rel','stylesheet');
            girl_link.setAttribute('href','https://cdn.jsdelivr.net/npm/font-awesome/css/font-awesome.min.css');
            girl_link.setAttribute('id','girl_link');
            iiframe.document.head.appendChild(girl_link);
            //添加script元素
            girl_script=iiframe.document.createElement('script');
            girl_script.setAttribute('src','https://cdn.jsdelivr.net/gh/stevenjoezhang/live2d-widget@latest/autoload.js');
            girl_script.setAttribute('id','girl_script');
            iiframe.document.head.appendChild(girl_script);}
 
    }
 
    //在内嵌iframe页面删除看板娘
    function deleteGirl(){
        window.alert('delete');
        iiframe = document.getElementById('#iframeautoheight').contentWindow;
        iiframe.document.querySelector('#live2d').remove();
    }
 
    //左下角添加看板娘(全局作用，慎用)
    function createGirl(){
        var girl_link = document.createElement('link');
        girl_link.setAttribute('hreflang','zh');
        girl_link.setAttribute('rel','stylesheet');
        girl_link.setAttribute('href','https://cdn.jsdelivr.net/npm/font-awesome/css/font-awesome.min.css');
        document.head.appendChild(girl_link);
        var girl_script=document.createElement('script');
        girl_script.setAttribute('src','https://cdn.jsdelivr.net/gh/stevenjoezhang/live2d-widget@latest/autoload.js');
        document.head.appendChild(girl_script);
    }
 
})();
