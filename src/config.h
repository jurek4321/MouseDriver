/*
 * config.h
 *
 *  Created on: 20.11.2017
 *      Author: user
 */

#ifndef CONFIG_H_
#define CONFIG_H_
class config{
public:
void init();
char* readmouse(int mouse);
bool writemouse(int mouse,char* code);

};
#endif /* CONFIG_H_ */
