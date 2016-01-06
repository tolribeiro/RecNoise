//
//  InfoViewController.h
//  Recife SM
//
//  Created by Tico on 11/11/15.
//  Copyright (c) 2015 Thiago Ribeiro. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface InfoViewController : UIViewController
@property (weak, nonatomic) IBOutlet UILabel *nameLabel;
@property (weak, nonatomic) NSString *namePlace;
@property (weak, nonatomic) IBOutlet UIImageView *imageLogo;
@property (weak, nonatomic) NSString *nameImage;
@property (weak, nonatomic) IBOutlet UILabel *valueLabel;
@property (weak, nonatomic) NSString *valueReal;
@end
