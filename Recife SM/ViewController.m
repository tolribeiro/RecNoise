//
//  ViewController.m
//  Recife SM
//
//  Created by Tico on 11/10/15.
//  Copyright (c) 2015 Thiago Ribeiro. All rights reserved.
//

#import "ViewController.h"
#import "Annotation.h"
#import "InfoViewController.h"

@interface ViewController () 

@property (weak, nonatomic) IBOutlet MKMapView *mapView;
@property (nonatomic, strong) NSMutableData *responseData;
@property (nonatomic, strong) NSString *value;

@end

@implementation ViewController

@synthesize responseData = _responseData;

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    [_mapView setMapType:MKMapTypeStandard];
    [_mapView setZoomEnabled:YES];
    [_mapView setScrollEnabled:YES];
    [_mapView setDelegate:self];
    
    MKCoordinateRegion downTownPub = { {0.0, 0.0} , {0.0, 0.0} };
    downTownPub.center.latitude = -8.063790;
    downTownPub.center.longitude = -34.872174;
    downTownPub.span.longitudeDelta = 0.003f;
    downTownPub.span.latitudeDelta = 0.003f;
    [_mapView setRegion:downTownPub animated:YES];
    
    Annotation *ann1 = [[Annotation alloc] init];
    ann1.title = @"Downtown Pub";
    ann1.subtitle = @"Casa de Show";
    ann1.coordinate = downTownPub.center;
    [_mapView addAnnotation: ann1];
    
    MKCoordinateRegion rockAndRibs = { {0.0, 0.0} , {0.0, 0.0} };
    rockAndRibs.center.latitude = -8.063662;
    rockAndRibs.center.longitude = -34.871336;
    rockAndRibs.span.longitudeDelta = 0.003f;
    rockAndRibs.span.latitudeDelta = 0.003f;
    [_mapView setRegion:rockAndRibs animated:YES];
    
    Annotation *ann2 = [[Annotation alloc] init];
    ann2.title = @"Rock & Ribs Lounge";
    ann2.subtitle = @"Bar Restaurante";
    ann2.coordinate = rockAndRibs.center;
    [_mapView addAnnotation:ann2];
    
    MKCoordinateRegion centroCultura = { {0.0, 0.0} , {0.0, 0.0} };
    centroCultura.center.latitude = -8.062533;
    centroCultura.center.longitude = -34.871348;
    centroCultura.span.longitudeDelta = 0.003f;
    centroCultura.span.latitudeDelta = 0.003f;
    [_mapView setRegion:centroCultura animated:YES];
    
    Annotation *ann3 = [[Annotation alloc] init];
    ann3.title = @"Centro de Cultura";
    ann3.subtitle = @"Turismo/Lazer";
    ann3.coordinate = centroCultura.center;
    [_mapView addAnnotation:ann3];
    
    MKCoordinateRegion bistroBoteco = { {0.0, 0.0} , {0.0, 0.0} };
    bistroBoteco.center.latitude = -8.062155;
    bistroBoteco.center.longitude = -34.870680;
    bistroBoteco.span.longitudeDelta = 0.003f;
    bistroBoteco.span.latitudeDelta = 0.003f;
    [_mapView setRegion:bistroBoteco animated:YES];
    
    Annotation *ann4 = [[Annotation alloc] init];
    ann4.title = @"Bistrô & Boteco";
    ann4.subtitle = @"Restaurante";
    ann4.coordinate = bistroBoteco.center;
    [_mapView addAnnotation:ann4];
}

-(MKAnnotationView *) mapView:(MKMapView *)mapView viewForAnnotation:(id<MKAnnotation>)annotation {
    MKAnnotationView *MyPin=[[MKAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:@"current"];
    
    //MyPin.pinColor = MKPinAnnotationColorRed;
    
    MyPin.image = [UIImage imageNamed:@"CustomPin"];
    
    //UIButton *advertButton = [UIButton buttonWithType:UIButtonTypeDetailDisclosure];
    UIButton *advertButton = [[UIButton alloc]init];
    [advertButton setBackgroundImage:[UIImage imageNamed:@"rightArrow"] forState:UIControlStateNormal];
    [advertButton sizeToFit];
    MyPin.rightCalloutAccessoryView = advertButton;
    MyPin.draggable = NO;
    MyPin.highlighted = YES;
    //MyPin.animatesDrop=TRUE;
    MyPin.canShowCallout = YES;
    
    return MyPin;
    
}

-(void)mapView:(MKMapView *)mapView annotationView:(MKAnnotationView *)view calloutAccessoryControlTapped:(UIControl *)control
{
    [self performSegueWithIdentifier:@"Show Info" sender:view];
}

-(void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if ([sender isKindOfClass:[MKAnnotationView class]]){
        [self prepareViewController:segue.destinationViewController forSegue:segue.identifier toShowAnnotation:((MKAnnotationView*)sender).annotation];
    }
}

-(void)prepareViewController:(id)vc
                    forSegue:(NSString*)segueIdentifier
            toShowAnnotation:(id<MKAnnotation>)annotation {
    
    
    if ([vc isKindOfClass:[InfoViewController class]]) {
        NSLog(@"%@", annotation.title);
        InfoViewController *info = (InfoViewController *)vc;
        info.namePlace = annotation.title;
        
        if ([info.namePlace isEqualToString:@"Rock & Ribs Lounge"])
            info.nameImage = @"rockAndRibs";
        if ([info.namePlace isEqualToString:@"Downtown Pub"])
            info.nameImage = @"down";
        
        NSData *lastSoundData = [[NSData alloc] initWithContentsOfURL:
                                 [NSURL URLWithString:@"http://api.thingspeak.com/channels/53759/feed/last.json?key=IGPEC0UJCH5I6IAY"]];
        
        
        NSError *error;
        NSMutableDictionary *data = [NSJSONSerialization
                                     JSONObjectWithData:lastSoundData
                                     options:kNilOptions
                                     error:&error];
        
        if( error )
        {
            NSLog(@"%@", [error localizedDescription]);
        }
        else {
            NSString *valor = [data objectForKey:@"field1"];
            NSLog(@"%@",valor);
            valor = [valor stringByAppendingString:@" dB"];
            NSLog(@"%@",valor);
            _value = valor;
        }
        
        info.valueReal = _value;
    }
    
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
