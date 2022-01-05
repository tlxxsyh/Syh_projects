// ==UserScript==
// @name         SYUCT沈阳化工大学教务系统助手
// @namespace    http://tampermonkey.net/
// @version      1.6
// @description  提供按下回车一键自动填写评价功能，iframe框架内显示看板娘功能
// @author       Yuhang Shang
// @match        *://jws.syuct.edu.cn/*
// @icon         https://www.shangyuhang.icu/favicon/64_64.ico
// @grant        none
// @license      MIT
// ==/UserScript==
 
(function() {
    'use strict';
    //使用帮助
    //在使用脚本按键前请先点击页面，使脚本能够获取焦点
    //按下回车键自动填写教师评价（默认第一行是良好，其余行均为优秀）
 
    var your_username='你的学号';
    var your_password='你的密码';
 
    //全局变量
    var StudentLoginURL='default2.aspx';
    var iiframe;
    var girl_link;
    var girl_script;
 
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
        let rows=document.querySelector('#DataGrid1').rows.length-1;
        for(let i=0;i<rows;i++){
            let my_selector='#DataGrid1__ctl'+(i+2)+'_JS1';
            document.querySelector(my_selector).value='优秀';
            console.log(my_selector);
        }
        var final=document.getElementById('DataGrid1__ctl2_JS1');
        final.value='良好';
        document.querySelector('#Button1').click();
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
 
//我把这些历史遗留的解决思路放在这里,以备不时之需
 
/*
//这个代码无法直接执行，需要点击选中元素才能执行，解决方法未知
    function write2(){
        let rows=document.querySelector('#DataGrid1').rows.length-1;
        for(let i=0;i<rows;i++){
            let my_selector='#DataGrid1__ctl'+(i+2)+'_JS1';
            document.querySelector(my_selector).value='良好';
            console.log(my_selector);}
    }
*/
 
/*function write(){
        var a=document.getElementById('DataGrid1__ctl2_JS1');
        a.value='良好';
        if(a=document.getElementById('DataGrid1__ctl3_JS1'))
        {
            a.value='优秀';
        }
        if(a=document.getElementById('DataGrid1__ctl4_JS1'))
        {
            a.value='优秀';
        }
        if(a=document.getElementById('DataGrid1__ctl5_JS1'))
        {
            a.value='优秀';
        }
        if(a=document.getElementById('DataGrid1__ctl6_JS1'))
        {
            a.value='优秀';
        }
        if(a=document.getElementById('DataGrid1__ctl7_JS1'))
        {
            a.value='优秀';
        }
        if(a=document.getElementById('DataGrid1__ctl8_JS1'))
        {
            a.value='优秀';
        }
        if(a=document.getElementById('DataGrid1__ctl9_JS1'))
        {
            a.value='优秀';
        }
        if(a=document.getElementById('DataGrid1__ctl10_JS1'))
        {
            a.value='优秀';
        }
        if(a=document.getElementById('DataGrid1__ctl11_JS1'))
        {
            a.value='优秀';
        }
        if(a=document.getElementById('DataGrid1__ctl12_JS1'))
        {
            a.value='优秀';
        }
        if(a=document.getElementById('DataGrid1__ctl13_JS1'))
        {
            a.value='优秀';
        }
        if(a=document.getElementById('DataGrid1__ctl14_JS1'))
        {
            a.value='优秀';
        }
        if(a=document.getElementById('DataGrid1__ctl15_JS1'))
        {
            a.value='优秀';
        }
        if(a=document.getElementById('DataGrid1__ctl16_JS1'))
        {
            a.value='优秀';
        }
        if(a=document.getElementById('DataGrid1__ctl17_JS1'))
        {
            a.value='优秀';
        }
        if(a=document.getElementById('DataGrid1__ctl18_JS1'))
        {
            a.value='优秀';
        }
        if(a=document.getElementById('DataGrid1__ctl19_JS1'))
        {
            a.value='优秀';
        }
        if(a=document.getElementById('DataGrid1__ctl20_JS1'))
        {
            a.value='优秀';
        }
        if(a=document.getElementById('DataGrid1__ctl21_JS1'))
        {
            a.value='优秀';
        }
        document.querySelector('#pjxx').value='非常好';
        //document.querySelector('#Button1').click();
    }
    */
