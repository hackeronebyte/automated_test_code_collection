md_commodity_search()
/*
  微商补货搜索商品三步
  
*/
{
	char base_str1[500],base_str2[500],base_str3[500],itemid_or_barcode[20],supply_unit_num_id[20];
    //获取固定代理商ID supply_unit_num_id
	strcpy(supply_unit_num_id,lr_eval_string(mendian_supply_unit_num_id()));
	lr_save_string(supply_unit_num_id,"supply_unit_num_id");;
    //获取固定代理商的固定商品ID
	strcpy(itemid_or_barcode,lr_eval_string(mendian_itemid_barcode()));
	lr_save_string(itemid_or_barcode,"itemid_or_barcode");

    //搜索1
    strcpy(base_str1,lr_eval_string("{\"sql_id\":\"YKPPAY-00944\",\"on_line\":true,\"input_param\":{\"item_num_id_or_item_name_or_itemid_or_barcode\":\"{itemid_or_barcode}\"},\"page_num\":1,\"page_size\":0}"));
	lr_save_string(base_str1,"base_str1");
	strcpy(base_str1,base64_encode(lr_eval_string("{base_str1}"),strlen(base_str1)));
	lr_save_string(base_str1,"base_str1");
	web_reg_find("Text=\"code\":0","Savecount=md_commodity_search1_code_count",LAST);//设置检查点
    web_add_header("Authorization","{md_author}");
	web_set_sockets_option("SSL_VERSION","TLS");
    lr_start_transaction("md_commodity_search1_YKPPAY-0094");
    web_custom_request("md_commodity_search1",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=hg.poykl.data.export&sid={md_sid}&sign=&params={base_str1}",
		LAST);
	if(atoi(lr_eval_string("{md_commodity_search1_code_count}"))>0){
			lr_end_transaction("md_commodity_search1_YKPPAY-0094",LR_PASS);
		}else{
            lr_end_transaction("md_commodity_search1_YKPPAY-0094",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		} 

    //搜索2
    strcpy(base_str2,lr_eval_string("{\"sql_id\":\"YKPPAY-0115\",\"on_line\":true,\"input_param\":{\"item_num_id\":{itemid_or_barcode}},\"page_num\":1,\"page_size\":99999}"));
	lr_save_string(base_str2,"base_str2");
	strcpy(base_str2,base64_encode(lr_eval_string("{base_str2}"),strlen(base_str2)));
	lr_save_string(base_str2,"base_str2");// 编码base64
	web_reg_find("Text=\"code\":0","Savecount=md_commodity_search2_code_count",LAST);//设置检查点

	web_add_header("Authorization","{md_author}");
	web_set_sockets_option("SSL_VERSION","TLS");
    lr_start_transaction("md_commodity_search2-YKPPAY-0115");
    web_custom_request("md_commodity_search2",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=hg.poykl.data.export&sid={md_sid}&sign=&params={base_str2}",
		LAST);
	if(atoi(lr_eval_string("{md_commodity_search2_code_count}"))>0){
			lr_end_transaction("md_commodity_search2-YKPPAY-0115",LR_PASS);
		}else{
            lr_end_transaction("md_commodity_search2-YKPPAY-0115",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		} 



    //搜索3
    strcpy(base_str3,lr_eval_string("{\"business_type\":10001,\"type_num_id\":1,\"sub_unit_num_id\":{md_sub_unit_num_id},\"barcode\":\"{itemid_or_barcode}\",\"supply_unit_num_id\":{supply_unit_num_id},\"logistics_type\":0,\"div_num_id\":0,\"order_date\":\"{order_date}\"}"));
	lr_save_string(base_str3,"base_str3");
	strcpy(base_str3,base64_encode(lr_eval_string("{base_str3}"),strlen(base_str3)));
	lr_save_string(base_str3,"base_str3");// 编码base64
	web_reg_find("Text=\"code\":0","Savecount=md_commodity_search3_code_count",LAST);//设置检查点

	web_add_header("Authorization","{md_author}");
	web_set_sockets_option("SSL_VERSION","TLS");
    lr_start_transaction("md_commodity_search3");
    web_custom_request("md_commodity_search3",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=hg.poykl.data.export&sid={md_sid}&sign=&params={base_str1}",
		LAST);
	if(atoi(lr_eval_string("{md_commodity_search3_code_count}"))>0){
			lr_end_transaction("md_commodity_search3",LR_PASS);
		}else{
            lr_end_transaction("md_commodity_search3",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		} 

    
	return 0;
}
