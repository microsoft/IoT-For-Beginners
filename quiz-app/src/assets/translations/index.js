// index.js
import ar from './ar.json';
import bn from './bn.json';
import en from './en.json';
import zh_cn from './zh-cn.json';

//export const defaultLocale = 'en';

const messages = {
	ar: ar[0],
	bn: bn[0],
	en: en[0],
	"zh-cn": zh_cn[0],
};

export default messages;
