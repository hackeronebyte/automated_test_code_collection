zd_fhtzd_query()
/**
 * 总商发货通知单查询
 */
{

    char base_str1[1024],url[50],zd_so_num_id[50];
	strcpy(url,lr_eval_string(base_url()));
    lr_save_string(url,"url");

	//查询全部
	strcpy(base_str1,lr_eval_string("{\"sql_id\":\"YKPPAY-SCM-02355\",\"on_line\":true,\"input_param\":{\"order_date_b\":\"{today}\",\"sub_unit_num_id\":\"{zd_sub_unit_num_id}\",\"order_date_e\":\"2021-12-01\"},\"page_num\":1,\"page_size\":100}"));
	lr_convert_string_encoding(base_str1, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str1" );
	strcpy(base_str1,lr_eval_string("{base_str1}"));
	lr_save_string(base_str1,"base_str1");
	strcpy(base_str1,base64_encode(lr_eval_string("{base_str1}"),strlen(base_str1)));
	lr_save_string(base_str1,"base_str1");
	web_reg_find("Text=\"code\":0","Savecount=fhtzd_query_all_code_count",LAST);//设置检查点
    //"so_num_id":"1801120831000000010",
	web_reg_save_param("zd_so_num_id","RB=\",","LB=\"so_num_id\":\"","ORD=ALL",LAST);//用关联函数取值 
	web_add_header("Authorization","{zd_author}");
	web_set_sockets_option("SSL_VERSION","TLS");
	lr_start_transaction("YKPPAY-SCM-02355");
	web_custom_request("fhtzd_query_all",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=hg.poykl.data.export&sid={zd_sid}&sign=&params={base_str1}",
		LAST);
	if(atoi(lr_eval_string("{fhtzd_query_all_code_count}"))>0){
			lr_end_transaction("YKPPAY-SCM-02355",LR_PASS);
		}else{
			lr_end_transaction("YKPPAY-SCM-02355",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}
     sprintf(zd_so_num_id,"{zd_so_num_id_%d}",rand()%(atoi(lr_eval_string("{zd_so_num_id_count}")))+1);
	lr_save_string (lr_eval_string(zd_so_num_id),"zd_so_num_id" );
	return 0;
}
