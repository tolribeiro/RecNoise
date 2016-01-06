//
//  InfoViewController.m
//  Recife SM
//
//  Created by Tico on 11/11/15.
//  Copyright (c) 2015 Thiago Ribeiro. All rights reserved.
//

#import "InfoViewController.h"
#import "Annotation.h"

@interface InfoViewController ()

@end

@implementation InfoViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    _nameLabel.text = _namePlace;
    [_imageLogo setImage:[UIImage imageNamed:_nameImage]];
    self.imageLogo.layer.cornerRadius = self.imageLogo.frame.size.width / 2;
    _valueLabel.text = _valueReal;

}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
