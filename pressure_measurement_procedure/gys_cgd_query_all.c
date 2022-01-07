gys_cgd_query_all()
/**
 * 代理商查询
 * 1、所有订购单
 * 2、单个订单
 */
{
	char base_str1[1024],base_str2[1024],url[50],all_gys_po_num_id[10];
	strcpy(url,lr_eval_string(gys_base_url("/gateway")));
    lr_save_string(url,"url");

    //查询所有记录
	strcpy(base_str1,lr_eval_string("{\"sql_id\":\"SUPPLIER_ORDER_001\","
									"\"input_param\":{\"supply_unit_num_id\":\"{supply_unit_num_id}\","
									"\"po_num_id\":\"\",\"begin_dtme\":\"2021-12-01\","
									"\"end_dtme\":\"{today}\",\"approval_num_id\":\"\","
									"\"status_num_id\":\"2\",\"po_type_id\":\"\","
									"\"logistics_type\":\"\"},\"page_num\":1,\"page_size\":10,"
									"\"data_sign\":\"0\",\"tenant_num_id\":\"{gysmerchantid_value}\"}"));
	lr_convert_string_encoding(base_str1, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str1" );
	strcpy(base_str1,lr_eval_string("{base_str1}"));
	lr_save_string(base_str1,"base_str1");
	strcpy(base_str1,base64_encode(lr_eval_string("{base_str1}"),strlen(base_str1)));
	lr_save_string(base_str1,"base_str1");


	web_reg_find("Text=\"code\":0","Savecount=gys_cgd_query_all_code_count",LAST);//设置检查点
	//"po_num_id":"14011222000001002",代理商采购单号
    web_reg_save_param("all_gys_po_num_id","RB=\",","LB=\"po_num_id\":\"","ORD=ALL",LAST);//用关联函数取值 
    web_set_sockets_option("SSL_VERSION","TLS");
    lr_start_transaction("SUPPLIER_ORDER_001");
	web_custom_request("gys_cgd_query_all",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=method=hg.poykl.data.export&params={base_str1}&sid={gys_sid}&timestamp={timestamp}&sign=",
		LAST);
	if(atoi(lr_eval_string("{gys_cgd_query_all_code_count}"))>0){
			lr_end_transaction("SUPPLIER_ORDER_001",LR_PASS);
		}else{
			lr_end_transaction("SUPPLIER_ORDER_001",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		} 
    sprintf(all_gys_po_num_id,"{all_gys_po_num_id_%d}",rand()%(atoi(lr_eval_string("{all_gys_po_num_id_count}")))+1);
	lr_save_string (lr_eval_string(all_gys_po_num_id),"all_gys_po_num_id" );

	//查询单个记录
    strcpy(base_str2,lr_eval_string("{\"sql_id\":\"SUPPLIER_ORDER_001\","
									"\"input_param\":{\"supply_unit_num_id\":\"{supply_unit_num_id}\","
									"\"po_num_id\":\"{all_gys_po_num_id}\","
									"\"begin_dtme\":\"2021-12-01\",\"end_dtme\":\"{today}\","
									"\"approval_num_id\":\"\",\"status_num_id\":\"2\",\"po_type_id\":\"\","
									"\"logistics_type\":\"\"},\"page_num\":1,\"page_size\":10,\"data_sign\":\"0\","
									"\"tenant_num_id\":\"{gysmerchantid_value}\"}"));
	lr_convert_string_encoding(base_str2, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str2" );
	strcpy(base_str2,lr_eval_string("{base_str2}"));
	lr_save_string(base_str2,"base_str2");
	strcpy(base_str2,base64_encode(lr_eval_string("{base_str2}"),strlen(base_str2)));
	lr_save_string(base_str2,"base_str2");


	web_reg_find("Text=\"code\":0","Savecount=gys_cgd_query_single_code_count",LAST);//设置检查点
    //"order_date":"2021-12-28 00:00:00",下单时间
	web_reg_save_param("gys_order_date","RB=\",","LB=\"order_date\":\"",LAST);//用关联函数取值 
	//"sub_unit_num_id":100049, 总商微商ID
	web_reg_save_param("gys_sub_unit_num_id","RB=,","LB=\"sub_unit_num_id\":",LAST);//用关联函数取值 
	//"supply_unit_num_id":"4116", 代理商ID
	web_reg_save_param("gys_supply_unit_num_id","RB=\",","LB=\"supply_unit_num_id\":\"",LAST);//用关联函数取值 
	//"po_num_id":"14011222000001002", 代理商采购单号
	web_reg_save_param("gys_po_num_id","RB=\",","LB=\"po_num_id\":\"",LAST);//用关联函数取值 
	lr_start_transaction("SUPPLIER_ORDER_001");
	web_custom_request("gys_cgd_query_single",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=method=hg.poykl.data.export&params={base_str2}&sid={gys_sid}&timestamp={timestamp}&sign=",
		LAST);
	if(atoi(lr_eval_string("{gys_cgd_query_single_code_count}"))>0){
			lr_end_transaction("SUPPLIER_ORDER_001",LR_PASS);
		}else{
			lr_end_transaction("SUPPLIER_ORDER_001",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		} 

	return 0;
}
